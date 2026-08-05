# STM32 Template Project

Ce dépôt est le **super-projet** du framework STM32. Il rassemble le framework
FMK, les bibliothèques communes, les modules applicatifs, les configurations
propres à la carte et les outils de génération de code. Une partie de ces
composants est intégrée sous forme de sous-modules Git.

L'objectif est de conserver une logique applicative indépendante du
microcontrôleur. Les éléments liés au matériel (horloges, GPIO, interruptions,
DMA, instances HAL, etc.) restent isolés dans les fichiers de configuration
spécifiques à la cible.

> [!IMPORTANT]
> À ce jour, le projet est configuré et validé uniquement pour les
> **STM32G474RE** et **STM32H753ZI**. La prise en charge d'un autre STM32
> nécessite un portage et une validation supplémentaires.

## Sommaire

- [Prérequis](#prérequis)
- [Installation](#installation)
- [Choisir la cible](#choisir-la-cible)
- [Générer la configuration](#générer-la-configuration)
- [Compiler, flasher et déboguer](#compiler-flasher-et-déboguer)
- [Ajouter la logique applicative](#ajouter-la-logique-applicative)
- [Organisation du dépôt](#organisation-du-dépôt)
- [Documentation](#documentation)
- [Limites actuelles](#limites-actuelles)

## Prérequis

- Git ;
- Python 3 ;
- Microsoft Excel, nécessaire pour modifier les fichiers de configuration ;
- Visual Studio Code ;
- l'extension **PlatformIO IDE** pour Visual Studio Code ;
- la plateforme PlatformIO **ST STM32** ;
- une sonde ST-Link compatible avec la carte utilisée ;
- Draw.io, ou son extension Visual Studio Code, pour consulter les diagrammes
  d'architecture.

## Installation

Cloner le super-projet avec tous ses sous-modules :

```bash
git clone --recurse-submodules \
  https://github.com/mbarbeau0545/Stm32TemplateProject.git
cd Stm32TemplateProject
```

Pour une copie déjà clonée sans les sous-modules :

```bash
git submodule update --init --recursive
```

Les sous-modules suivent actuellement leur branche `Dev`. Après une mise à jour
du super-projet, synchroniser les révisions attendues avec :

```bash
git submodule sync --recursive
git submodule update --init --recursive
```

## Choisir la cible

La cible PlatformIO active est définie dans
[`platformio.ini`](platformio.ini). La configuration fournie active la carte
Nucleo H753ZI :

```ini
[env:nucleo_h753zi]
board = nucleo_h753zi
```

Les deux cibles actuellement prises en charge sont :

| Microcontrôleur | Carte PlatformIO | Configuration matérielle |
| --- | --- | --- |
| STM32H753ZI | `nucleo_h753zi` | `Doc/ConfigPrj/ExcelCfg/STM32H753ZI/STM32H753ZI_HwCfg.xlsx` |
| STM32G474RE | `nucleo_g474re` | `Doc/ConfigPrj/ExcelCfg/STM32G474RE/STM32G474RE_HwCfg.xlsx` |

Pour changer de cible :

1. sélectionner la carte correspondante dans `platformio.ini` ;
2. vérifier les options propres à la cible, notamment le script de linker ;
3. régénérer les fichiers de configuration avec le classeur matériel de cette
   cible ;
4. nettoyer le précédent build avant de recompiler.

Le script de linker
`linker/STM32H753ZITX_FLASH_FMKNVM.ld` est spécifique au STM32H753ZI et réserve
une zone Flash au module FMK NVM. Il ne doit pas être utilisé tel quel pour le
STM32G474RE.

## Générer la configuration

La configuration du projet est produite à partir de :

- un classeur matériel propre au microcontrôleur dans
  `Doc/ConfigPrj/ExcelCfg/<cible>/` ;
- le classeur logiciel
  `Doc/ConfigPrj/ExcelCfg/Project_SoftwareCfg_V0.xlsm`.

Avant la génération :

1. renseigner le classeur matériel avec les informations de la documentation
   ST : IRQ, clocks RCC, GPIO, fonctions alternatives, timers, ADC, DAC et DMA ;
2. configurer les modules applicatifs dans le classeur logiciel ;
3. enregistrer et fermer les classeurs pour éviter qu'Excel ne conserve un
   fichier temporaire ou un verrou.

Depuis la racine du dépôt, lancer le générateur avec la cible souhaitée.

Pour le STM32H753ZI :

```powershell
python Doc/ConfigPrj/PythonTool_CodeGen/main.py `
  Doc/ConfigPrj/ExcelCfg/STM32H753ZI/STM32H753ZI_HwCfg.xlsx `
  Doc/ConfigPrj/ExcelCfg/Project_SoftwareCfg_V0.xlsm
```

Pour le STM32G474RE :

```powershell
python Doc/ConfigPrj/PythonTool_CodeGen/main.py `
  Doc/ConfigPrj/ExcelCfg/STM32G474RE/STM32G474RE_HwCfg.xlsx `
  Doc/ConfigPrj/ExcelCfg/Project_SoftwareCfg_V0.xlsm
```

Contrôler les différences Git après chaque génération avant de compiler :

```bash
git status --short
git diff
```

## Compiler, flasher et déboguer

Les commandes suivantes s'exécutent depuis la racine du dépôt.

Compiler la cible embarquée active :

```bash
pio run -e nucleo_h753zi
```

Flasher avec ST-Link :

```bash
pio run -e nucleo_h753zi -t upload
```

Nettoyer les fichiers de build :

```bash
pio run -e nucleo_h753zi -t clean
```

Le dépôt contient aussi l'environnement `pc_sim_debug`, destiné à la simulation
sur PC d'une partie du projet :

```bash
pio run -e pc_sim_debug
```

Cet environnement ne remplace pas les essais sur la cible réelle.

## Ajouter la logique applicative

La logique propre au produit se trouve dans :

```text
src/3_APP/APP_LGC/Src/APP_LGC.c
```

- `APPLGC_Init()` contient l'initialisation exécutée au démarrage du module ;
- `APPLGC_Cyclic()` contient le traitement cyclique ;
- l'application utilise les API publiques des modules FMK et ne manipule pas
  directement leurs handles HAL.

Les fichiers générés dans `src/1_FMK/FMK_CFG` et `src/3_APP/APP_CFG` doivent
être modifiés via les sources de configuration lorsque cela est possible, afin
qu'une nouvelle génération ne perde pas les changements.

## Organisation du dépôt

| Répertoire | Rôle |
| --- | --- |
| `src/0_Common` | Types communs et bibliothèques génériques |
| `src/1_FMK/FMK_HAL` | Modules matériels du framework |
| `src/1_FMK/FMK_CFG` | Configuration publique, privée et spécifique à la cible |
| `src/2_DRV` | Drivers de composants externes |
| `src/3_APP` | Modules et logique applicatifs |
| `src/4_PCSIM` | Adaptation et simulation sur PC |
| `Doc/ConfigPrj` | Classeurs et outils de génération |
| `Doc/InfoPrj` | Architecture, notes techniques et documentation Doxygen |

## Documentation

- Les diagrammes Draw.io se trouvent dans les répertoires `Doc` des modules et
  dans `Doc/InfoPrj`.
- La documentation Doxygen générée est accessible depuis
  `Doc/InfoPrj/Doxygen/html/index.html`.
- Les notes de configuration générales se trouvent dans
  `Doc/InfoPrj/InfoCfg`.
- Certains modules possèdent également leur propre `README.md`.

## Limites actuelles

- La compatibilité est validée uniquement sur **STM32G474RE** et
  **STM32H753ZI**, avec les configurations fournies dans le dépôt.
- Le simple changement de la valeur `board` dans `platformio.ini` ne suffit pas
  pour prendre en charge un nouveau microcontrôleur.
- Une nouvelle cible demande au minimum une configuration HAL et FMK spécifique,
  un classeur matériel, une configuration des pins, clocks, IRQ et DMA, ainsi
  qu'un script de linker adapté.
- Certains backends sont spécifiques à une famille ou à une cible. C'est
  notamment le cas du stockage en Flash interne et du script de linker NVM du
  STM32H753ZI.
- Les fichiers générés dépendent de la cohérence entre la cible PlatformIO, le
  classeur matériel et le classeur logiciel. Mélanger les configurations de
  deux cibles produit un build invalide ou un comportement matériel incorrect.
- La simulation PC ne couvre qu'une partie des accès matériels et ne valide ni
  les timings, ni les interruptions, ni les DMA, ni les périphériques réels.
- Les configurations présentes pour d'autres références STM32 sont des travaux
  historiques ou incomplets ; elles ne constituent pas des cibles supportées.
- Le projet et ses sous-modules évoluent encore sur la branche `Dev`. Une
  validation sur carte reste nécessaire après une mise à jour.
