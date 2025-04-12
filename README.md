# FalloutPickle

An advanced F4SE plugin for exporting and reimporting character and game state in Fallout 4.

Think of it like Python's `pickle`, but for your Sole Survivor.

---

## Features

- Export:
  - Character name, level, XP, SPECIAL, perks
  - Inventory, equipped gear
  - Quests and stages
  - Globals
  - Companion data (name, appearance, gear)
  - Map marker discoveries
  - Workshop details (with WSFW)

- Import:
  - FormID-resolved reapplication
  - Dry run and verbose logs
  - Optional flags and profiles

---

## Console Usage

pickle [flags] unpickle [flags]

Examples:
- `pickle +character +quests`
- `unpickle !workshops`
- `unpickle dryrun path=Exports/Nora_2025-04-12_08-30-00`

---

## Requirements

- Fallout 4
- F4SE
- Looksmenu (optional)
- Workshop Framework (optional)

---

## Output

Exported files live in `Data/Exports/<character>_<timestamp>/` and include:
- `Character.json`
- `Perks.json`
- `Globals.json`
- `Inventory.json`
- `Quests.json`
- `Map.json`
- `Companions.json`
- `Workshops.json`
- `ExportVerbose.log`
- `UnpickleVerbose.log`
- `FormResolution.log`

---

## Version

Current: `v0.2.8`

