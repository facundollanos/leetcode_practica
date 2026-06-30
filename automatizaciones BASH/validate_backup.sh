# validate_backup_dest.sh
#!/bin/bash

# Guardamos el primer argumento en una variable.
# Ejemplo: ./validate_backup_dest.sh /mnt/backups
# Entonces $1 vale /mnt/backups
dest="$1"

# Validamos que el usuario haya pasado un argumento.
# -z significa: "está vacío".
if [ -z "$dest" ]; then
    echo "Usage: $0 backup_directory"
    exit 1
fi

# Validamos que la ruta exista y sea un directorio.
# -d significa: "es un directorio".
# ! significa: "NO".
if [ ! -d "$dest" ]; then
    echo "Error: destination is not a directory"
    exit 1
fi

# Validamos que el usuario actual pueda escribir ahí.
# -w significa: "tiene permiso de escritura".
if [ ! -w "$dest" ]; then
    echo "Error: destination is not writable"
    exit 1
fi

echo "$dest is ready for backups"