# unique_ips.sh
#!/bin/bash

log="$1"

if [ -z "$log" ]; then
    echo "Usage: $0 log_file"
    exit 1
fi

if [ ! -f "$log" ]; then
    echo "Error: log file not found"
    exit 1
fi

# grep -E usa regex extendida.
# -o imprime solo lo que matchea, no toda la línea.
# sort -u ordena y elimina duplicados.
grep -Eo '([0-9]{1,3}\.){3}[0-9]{1,3}' "$log" |
sort -u