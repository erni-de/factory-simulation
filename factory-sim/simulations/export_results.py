#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Export OMNeT++ result files to clean CSV (semicolon-separated), without runattr/config clutter.

Usage (Windows CMD/PowerShell):
  python export_results.py vec  vectors_long.csv "*.vec"
  python export_results.py sca  scalars.csv      "*.sca"

Notes:
- On Windows CMD the wildcard (*.vec) is NOT expanded by the shell.
  This script expands glob patterns itself, so pass "*.vec" / "*.sca" as shown.
- Output delimiter is ';' to be Excel-friendly in many locales.
"""

import csv
import glob
import re
import sys
from pathlib import Path

# --- helpers -----------------------------------------------------------------

def clean_cfg(v: str) -> str:
    v = (v or "").strip()
    # values often look like: "\"parallelized\"" or "\"0.78 0.9 ...\""
    v = v.replace('\\"', '')
    v = v.replace('"', '')
    return v

def strip_quotes(s: str) -> str:
    s = (s or "").strip()
    if len(s) >= 2 and ((s[0] == '"' and s[-1] == '"') or (s[0] == "'" and s[-1] == "'")):
        return s[1:-1]
    return s

def expand_patterns(args):
    """Expand glob patterns on any OS (so it works also in Windows CMD)."""
    out = []
    for a in args:
        if any(ch in a for ch in "*?[]"):
            out.extend(glob.glob(a))
        else:
            out.append(a)

    # de-dup preserving order
    seen = set()
    res = []
    for x in out:
        if x not in seen:
            seen.add(x)
            res.append(x)
    return [Path(x) for x in res]

# --- regex -------------------------------------------------------------------

RUN_RE    = re.compile(r'^run\s+(.*)$')
ATTR_RE   = re.compile(r'^attr\s+(\S+)\s+(.*)$')
CONFIG_RE = re.compile(r'^config\s+(\S+)\s+(.*)$')

VECTOR_RE = re.compile(r'^vector\s+(\d+)\s+(\S+)\s+(\S+)\s+')
DATA_RE   = re.compile(r'^(\d+)\s+(\d+)\s+([0-9eE+.\-]+)\s+([0-9eE+.\-]+)\s*$')

# --- parsers -----------------------------------------------------------------

def parse_vec_file(path: Path):
    run_id = ""
    attrs = {}
    cfg = {}
    vectors = {}  # vid -> (module, name)

    with path.open("r", encoding="utf-8", errors="replace") as f:
        for line in f:
            line = line.strip()
            if not line:
                continue

            m = RUN_RE.match(line)
            if m:
                run_id = m.group(1).strip()
                attrs = {}
                cfg = {}
                vectors = {}
                continue

            m = ATTR_RE.match(line)
            if m:
                attrs[m.group(1)] = strip_quotes(m.group(2))
                continue

            m = CONFIG_RE.match(line)
            if m:
                cfg[m.group(1)] = m.group(2).strip()
                continue

            m = VECTOR_RE.match(line)
            if m:
                vid = int(m.group(1))
                module = m.group(2)
                name = m.group(3)
                vectors[vid] = (module, name)
                continue

            m = DATA_RE.match(line)
            if m:
                vid = int(m.group(1))
                event = int(m.group(2))
                t = m.group(3)
                val = m.group(4)
                module, name = vectors.get(vid, ("", ""))

                yield {
                    #"run": run_id,
                    #"configname": attrs.get("configname", ""),
                    "mode": clean_cfg(cfg.get("**.mode", "")),
                    "N": clean_cfg(cfg.get("**.N", "")),
                    "p": clean_cfg(cfg.get("**.p", "")),
                    "seedset": clean_cfg(cfg.get("seed-set", "")),
                    #"file": path.name,
                    "vectorId": vid,
                    "module": module,
                    "name": name,
                    "event": event,
                    "time": t,
                    "value": val,
                }

def parse_sca_file(path: Path):
    run_id = ""
    attrs = {}
    cfg = {}
    current_stat = None  # (module, statname)

    with path.open("r", encoding="utf-8", errors="replace") as f:
        for raw in f:
            line = raw.strip()
            if not line:
                continue

            m = RUN_RE.match(line)
            if m:
                run_id = m.group(1).strip()
                attrs = {}
                cfg = {}
                current_stat = None
                continue

            m = ATTR_RE.match(line)
            if m:
                attrs[m.group(1)] = strip_quotes(m.group(2))
                continue

            m = CONFIG_RE.match(line)
            if m:
                cfg[m.group(1)] = m.group(2).strip()
                continue

            # ignore parameter lines
            if line.startswith("par "):
                continue

            # scalar <module> <name> <value>
            if line.startswith("scalar "):
                parts = line.split()
                if len(parts) >= 4:
                    module, name, value = parts[1], parts[2], parts[3]
                    yield {
                        #"run": run_id,
                        #"configname": attrs.get("configname", ""),
                        "mode": clean_cfg(cfg.get("**.mode", "")),
                        "N": clean_cfg(cfg.get("**.N", "")),
                        "p": clean_cfg(cfg.get("**.p", "")),
                        "seedset": clean_cfg(cfg.get("seed-set", "")),
                        #"file": path.name,
                        "module": module,
                        "name": name,
                        "value": value,
                    }
                current_stat = None
                continue

            # statistic <module> "<name with spaces>"
            if line.startswith("statistic "):
                parts = line.split(maxsplit=2)
                if len(parts) == 3:
                    module = parts[1]
                    statname = strip_quotes(parts[2])
                    current_stat = (module, statname)
                else:
                    current_stat = None
                continue

            # field <fieldname> <value>   (belongs to the last "statistic")
            if line.startswith("field ") and current_stat:
                parts = line.split(maxsplit=2)
                if len(parts) == 3:
                    fieldname, value = parts[1], parts[2]
                    module, statname = current_stat
                    yield {
                        #"run": run_id,
                        #"configname": attrs.get("configname", ""),
                        "mode": clean_cfg(cfg.get("**.mode", "")),
                        "N": clean_cfg(cfg.get("**.N", "")),
                        "p": clean_cfg(cfg.get("**.p", "")),
                        "seedset": clean_cfg(cfg.get("seed-set", "")),
                        #"file": path.name,
                        "module": module,
                        # turn statistic fields into scalar-like rows:
                        "name": f"{statname}:{fieldname}",
                        "value": value,
                    }
                continue

            # bins / histogram lines are skipped to keep the file short

# --- exporters ---------------------------------------------------------------

def export_vec(out_csv: Path, inputs):
    fieldnames = ["mode","N","p","seedset","vectorId","module","name","event","time","value"]
    total = 0
    with out_csv.open("w", newline="", encoding="utf-8") as out:
        w = csv.DictWriter(out, fieldnames=fieldnames, delimiter=";")
        w.writeheader()
        for vecfile in inputs:
            for row in parse_vec_file(vecfile):
                w.writerow(row)
                total += 1
    return total

def export_sca(out_csv: Path, inputs):
    fieldnames = ["mode","N","p","seedset","module","name","value"]
    total = 0
    with out_csv.open("w", newline="", encoding="utf-8") as out:
        w = csv.DictWriter(out, fieldnames=fieldnames, delimiter=";")
        w.writeheader()
        for scafile in inputs:
            for row in parse_sca_file(scafile):
                w.writerow(row)
                total += 1
    return total

# --- main --------------------------------------------------------------------

def main():
    if len(sys.argv) < 4:
        print("Uso:")
        print("  python export_results.py vec OUT.csv [patterns.vec ...]")
        print("  python export_results.py sca OUT.csv [patterns.sca ...]")
        print("\nEsempi (Windows):")
        print('  python export_results.py vec vectors_long.csv "*.vec"')
        print('  python export_results.py sca scalars.csv "*.sca"')
        sys.exit(1)

    mode = sys.argv[1].lower()
    out_csv = Path(sys.argv[2])
    inputs = expand_patterns(sys.argv[3:])
    if not inputs:
        print("Errore: nessun file trovato (controlla path/pattern).")
        sys.exit(2)

    if mode == "vec":
        inputs = [p for p in inputs if p.suffix.lower() == ".vec"]
        if not inputs:
            print("Errore: nessun file .vec tra gli input.")
            sys.exit(2)
        n = export_vec(out_csv, inputs)
        print(f"OK: scritto {n} campioni vector in {out_csv}")
    elif mode == "sca":
        inputs = [p for p in inputs if p.suffix.lower() == ".sca"]
        if not inputs:
            print("Errore: nessun file .sca tra gli input.")
            sys.exit(2)
        n = export_sca(out_csv, inputs)
        print(f"OK: scritto {n} righe scalar/stat in {out_csv}")
    else:
        print("Errore: primo argomento deve essere 'vec' oppure 'sca'.")
        sys.exit(1)

if __name__ == "__main__":
    main()
