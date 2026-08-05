# Conventions du projet H7_Integration

Ce fichier définit les règles obligatoires pour toute modification dans ce dépôt. Les modules existants `FMK_FDCAN`, `FMK_SRL`, `FMK_TIM` et `FMK_I2C` servent de références architecturales.

## Project language

- All new or modified project content must be written in English.
- This rule applies to source code comments, Doxygen documentation, Markdown
  files, user-facing messages, configuration descriptions, tests, examples,
  issue templates and pull request templates.
- When modifying an existing section written in French, translate the affected
  section into English as part of the same change.
- Identifiers, technical terms and abbreviations must remain consistent with
  the existing project naming conventions.

## Architecture du dépôt

- `src/0_Common` : types communs et bibliothèques génériques, sans dépendance à un module FMK ou à une carte.
- `src/0_Common/Library` : composants réutilisables, par exemple `FIFO`, `QUEUE`, `SafeMem`.
- `src/1_FMK/FMK_HAL` : modules HAL du framework. Chaque module expose son API dans `Src/<module>.h` et son implémentation dans `Src/<module>.c`.
- `src/1_FMK/FMK_CFG/FMKCFG_ConfigFiles` : configuration générée ou propre au projet, publique/privée.
- `src/1_FMK/FMK_CFG/FMKCFG_ConfigSpecific` : éléments dépendants de la carte, du MCU, des pins, des IRQ, des DMA et des instances HAL.
- `src/3_APP` : code application. L’application utilise les APIs publiques FMK, jamais les handles HAL d’un module.

## Architecture des modules FMK

- Chaque module suit le préfixe de son domaine : `FMKI2C_`, `FMKSRL_`, `FMKFDCAN_`, etc.
- Toute API publique suit le modèle `FMKxxx_Init()`, `FMKxxx_Cyclic()`, `FMKxxx_GetState()` et `FMKxxx_SetState()` lorsque le module est cyclique.
- Les fonctions locales sont préfixées par `s_`, par exemple `s_FMKI2C_StartNextTask()`.
- Les interfaces destinées aux IRQ ou à l’infrastructure interne sont explicitement suffixées `_PRIVATE_`.
- Les handles HAL sont possédés par le module et configurés dans `FMKxxx_ConfigPrivate.h` ou `FMKxxx_ConfigSpecific.c`; aucune API utilisateur ne reçoit un handle HAL.
- Les GPIO, clocks, IRQ, DMA, instances HAL, timings et choix dépendants du MCU/carte restent dans `ConfigSpecific`.
- Les constantes de capacité, tailles de buffers, nombre de lignes et politiques générales restent dans `ConfigPublic` ou `ConfigPrivate` selon leur visibilité.

- Utiliser une machine à état lorsqu'une action s'étend sur plusieurs cycles, accède à un backend asynchrone ou comporte des étapes observables. `Init()` arme cette machine ; les accès matériels, la découverte et la restauration sont exécutés par `Cyclic()` dans des sous-états explicites.

## Buffers, FIFO et asynchronisme

- Pour une API IT/DMA, le module ne conserve jamais un pointeur vers un buffer applicatif après le retour de l’API.
- Le module copie les données TX dans une zone interne avant de démarrer la HAL.
- Les opérations asynchrones sont représentées par des descripteurs de tâches placés dans une FIFO.
- Une tâche référence une zone interne par index et taille (`startBuffer_u16`, `dataSize_u16`), jamais par un pointeur applicatif différé.
- Un buffer circulaire garde sa zone réservée jusqu’à la fin, l’erreur ou l’abandon de la tâche associée.
- Les zones réservées sont libérées dans l’ordre FIFO.
- Utiliser `Library/FIFO` pour gérer `head`, `tail`, le compteur, la lecture et l’écriture des descripteurs. Ne jamais lire ou modifier directement `head_u16`, `tail_u16`, `count_u16` ou `cfg_s` depuis un module FMK.
- Utiliser `LIBFIFO_Create`, `LIBFIFO_Push`, `LIBFIFO_Peek`, `LIBFIFO_Pop`, `LIBFIFO_Discard` et `LIBFIFO_GetCount`.
- Si la HAL est occupée, la tâche reste dans la FIFO et `Cyclic()` la relance ultérieurement. Une FIFO pleine ou un buffer sans place retourne `RC_WARNING_BUSY` sans écraser de données.

## Nommage

- Types : `t_e...` pour enum, `t_s...` pour structure, `t_u...` pour union, `t_cb...` pour callback.
- Variables : suffixe de type obligatoire, par exemple `Ret_e`, `idx_u8`, `size_u16`, `data_pu8`, `handle_ps`, `isReady_b`.
- Paramètres de fonction : préfixe `f_` et suffixe de type, par exemple `f_I2CLine_e`, `f_Data_pu8`, `f_Size_u16`.
- Variables globales : préfixe `g_`; constantes globales : préfixe `c_`.
- Enum de cardinalité : suffixe `_NB`.

## Style C obligatoire

- Un seul `return` par fonction, placé à la fin de la fonction.
- Stocker le résultat d’un appel dans `Ret_e`, `HalStatus_e`, `found_b`, etc., avant de le tester. Aucun appel de fonction dans une condition `if`.
- Cette interdiction s'applique aussi aux ternaires, boucles et opérateurs logiques : stocker d'abord le résultat dans une variable nommée.
- Une validation par bloc `if`/`else if`; ne pas concaténer des validations sans nécessité.
- Les accolades sont seules sur leur ligne.
- Découper les appels de fonction longs sur plusieurs lignes et aligner les arguments.
- Conserver des lignes aérées entre déclarations, blocs de traitement et retours.
- Déclarer et initialiser chaque variable au plus près de sa première
  utilisation, dans la portée la plus petite possible. Ne pas regrouper
  systématiquement toutes les variables en tête de fonction. Les variables
  utilisées pendant toute la fonction, comme `Ret_e`, peuvent rester au niveau
  de la fonction.
- Utiliser les commentaires de traitement au format : `//---- Description courte ----//`.
- Toute implémentation comporte des commentaires numérotés décrivant les étapes métier, par exemple `//---- 1- Calculate slot offset ----//` puis `//---- 2- Program backend record ----//`.
- Chaque implémentation de fonction doit être écrite sous forme développée, avec son bandeau, ses déclarations, des commentaires de traitement en anglais, des accolades sur lignes séparées et un unique `return` final. Les implémentations compactées sur une ligne sont strictement interdites.
- Toute structure de contrôle (`if`, `else`, `for`, `while`, `switch`, `case`) est obligatoirement développée : condition, accolade ouvrante, contenu et accolade fermante occupent des lignes séparées. Les formes telles que `if(...) { action; }` sont strictement interdites.
- Dans la mesure du possible, une ligne source ne dépasse pas 120 colonnes. Les déclarations, appels et conditions longues sont découpés et alignés.
- Dans un `typedef struct`, chaque membre reste entièrement sur une seule
  ligne : type, nom, point-virgule et commentaire `///<`. Les commentaires
  `///<` de tous les membres sont alignés dans la même colonne. Pour cette
  présentation, il est permis de dépasser la limite indicative de 80 colonnes.
  Il est interdit de séparer le type du nom du membre.

```c
/// @brief Holds the private operations of one selected backend.
typedef struct __t_sFMKXXX_BackendApi
{
    void * context_pv;                         ///< Opaque context.
    t_cbFMKXXX_BackendInit * Init_pcb;         ///< Init callback.
    t_cbFMKXXX_BackendRead * Read_pcb;         ///< Read callback.
} t_sFMKXXX_BackendApi;
```
- Pour une déclaration, une définition ou un appel sur plusieurs lignes, le
  premier argument reste sur la même ligne que le nom de fonction et les
  arguments suivants sont alignés sur le premier. La forme avec une parenthèse
  ouvrante seule en fin de ligne est interdite.

```c
t_eReturnCode FMKXXX_Function(   t_uint8 f_First_u8,
                                const void * f_Data_pv,
                                t_uint32 f_Size_u32);
```
- Toute machine à états utilise un `switch` sur son état public. Chaque `case` appelle une fonction locale dédiée à l'état. La fonction locale retourne uniquement son résultat ; les transitions vers `OPE` ou `ERROR` sont décidées au niveau du `switch`. Un retour `RC_WARNING_PENDING` conserve l'état courant.
- Mettre un bandeau avant chaque implémentation :

```c
/*********************************
 * FMKXXX_FunctionName
 *********************************/
```

## C formatting and API design

### Line length and wrapping

- Keep simple assignments on one line.
- Do not insert a line break immediately after `=` for a simple right-hand expression.
- Keep function declarations, definitions, and calls on one line when they fit within 120 characters.
- Use 140 characters only as an exceptional hard limit.
- Do not place one argument per line automatically.
- Break lines only at meaningful logical boundaries.
- Do not reformat existing code into an excessively vertical style.
- For a multiline function declaration, definition, or call, keep the first argument on the same line as the
  function name and align subsequent arguments with the first argument.
- Do not leave an opening parenthesis alone at the end of a function declaration, definition, or call line.
- Keep structure assignments and initializations compact when every resulting line remains readable.

```c
Slot_ps->txReservation_u16 = f_Task_ps->txReservation_u16;
Slot_ps->rxReservation_u16 = f_Task_ps->rxReservation_u16;
Slot_ps->result_s.eventKind_e = FMKSPI_TRANSFER_EVENT_TERMINAL;

static t_eReturnCode s_FMKXXX_CompleteResult(   t_eFMKXXX_Line f_Line_e,
                                                const t_sFMKXXX_Task * f_Task_ps,
                                                t_eFMKXXX_Status f_Status_e,
                                                t_uint32 f_HealthMask_u32);
```

### API and implementation consistency

- Preserve the existing FMK parameter naming scheme: `f_` prefix and a type suffix.
- Pass immutable input structures and buffers through `const` pointers.
- Pass small scalar identifiers and enum values by value.
- Use an explicit context structure when a group of state values is shared by several local operations; do not
  introduce a context structure only to hide an otherwise clear short parameter list.
- Keep local variables in the narrowest useful scope and initialize them close to their first use.
- Keep one final `return` per function and propagate call results through a named variable before testing them.
- Organize parameter validation as readable `if` / `else if` blocks before the processing section.
- Split a large function only when the extracted function represents a coherent operation or state, not merely to
  reduce the line count.
- Keep Doxygen on public APIs, callback typedefs, types, and local prototypes; implementation bodies retain only
  their function banner and numbered processing comments.

## Organisation des fichiers C

L’ordre attendu dans un `.c` FMK est :

1. En-tête de fichier.
2. Includes.
3. Defines.
4. Types locaux.
5. Variables globales/locales statiques.
6. Bloc `Local functions - Prototypes`, avec la Doxygen des fonctions `static`.
7. Implémentations publiques.
8. Callbacks HAL / handlers IRQ si le module les possède.
9. Implémentations des fonctions locales.

## Doxygen

- Toute API publique est documentée dans son `.h`, directement avant sa déclaration.
- Toute fonction déclarée par `typedef` (callback inclus) reçoit une Doxygen aussi complète qu'une API publique : rôle, contexte, durée de vie et propriété des buffers si applicable, chaque `@param[in]` et `@param[out]`, ainsi que les `@retval` attendus. Une simple phrase `@brief` est insuffisante.
- Toute fonction `static` est documentée dans le bloc de prototypes au début du `.c`.
- Ne pas dupliquer une Doxygen devant l’implémentation.
- Les implémentations conservent seulement leur bandeau `/* ... */`.
- Utiliser ce format :

```c
/**
 *  @brief      Description courte de l’action.
 *  @note       Détails de fonctionnement, contraintes et contexte.
 *
 *  @param[in]  f_Param_e  : Description et enum/type de référence.
 *  @param[out] f_Value_pu16 : Valeur produite si applicable.
 *
 *  @retval RC_OK                  @ref RC_OK
 *  @retval RC_ERROR_PARAM_INVALID @ref RC_ERROR_PARAM_INVALID
 */
```

- tous les typedef enum doit être préceder d'une documentation doxygen :
```c
///@brief this is a description for an enum
typedef enum 
{
    APP = 0,
    EPP = 1,

    NB
} t_eFMKxxx_descEnum
```
- tous les typedef structure doit être préceder d'une documentation doxygen :
```c
///@brief this is a description for a structure
typedef enum 
{
    APP = 0,
    EPP = 1,

    NB
} t_sFMKxxx_descstruct
```
- tous les variables globales static/const et define doit être préceder d'une documentation doxygen :
```c
///@brief this is a description for a variable
static const c_Fmkxx_descvariable

///@brief this is a description for a variable
static g_Fmkxx_descvariable
```

- Omettre `@param[out]` lorsqu’une fonction n’a pas de sortie pointeur.
- Documenter explicitement les contraintes de durée de vie des buffers et le comportement polling/IT/DMA.

## Vérification obligatoire

- Ne pas écraser ou annuler les changements utilisateur existants.
- Après une modification C/C++, lancer `pio run` depuis la racine du dépôt.
- Corriger les warnings introduits par la modification.
- Vérifier les espaces finaux avec `git diff --check` pour les fichiers modifiés.
- Pour une modification de bibliothèque, vérifier que ses APIs sont utilisées sans accès à ses internals.
