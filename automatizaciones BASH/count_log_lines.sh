# count_log_lines.sh
#!/bin/bash

log="$1"

# Verificamos si el usuario pasó un argumento.
if [ -z "$log" ]; then
    echo "Usage: $0 log_file"
    exit 1
fi

# -f verifica si existe y es archivo normal.
# No sirve para carpetas.
if [ ! -f "$log" ]; then
    echo "Error: log file not found"
    exit 1
fi

# wc -l cuenta líneas.
# El < "$log" hace que wc lea el archivo,
# pero sin imprimir el nombre del archivo en la salida.
lines=$(wc -l < "$log")

echo "$log has $lines lines"