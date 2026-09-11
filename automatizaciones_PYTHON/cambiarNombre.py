import os
import re
import sys

DATE_PATTERN = re.compile(
    r"(20\d{2})[-_ ](\d{1,2})[-_ ](\d{1,2})"
)


def build_new_name(filename):
    name, extension = os.path.splitext(filename)

    match = DATE_PATTERN.search(name)

    if not match:
        return None

    year = match.group(1)
    month = match.group(2).zfill(2)
    day = match.group(3).zfill(2)

    return f"{year}-{month}-{day} - Final{extension}"

    
def get_available_name(directory, new_name):
    candidate = new_name
    name, extension = os.path.splitext(new_name)
    counter = 2

    while os.path.exists(os.path.join(directory, candidate)):
        candidate = f"{name} ({counter}){extension}"
        counter += 1

    return candidate


def rename_finals(directory, apply_changes=False):
    if not os.path.isdir(directory):
        print(f"[ERROR] Invalid directory: {directory}")
        return False

    files = sorted(os.listdir(directory))

    for filename in files:
        old_path = os.path.join(directory, filename)

        if not os.path.isfile(old_path):
            continue

        new_name = build_new_name(filename)

        if new_name is None:
            print(f"[SKIP] No year found: {filename}")
            continue

        if filename == new_name:
            print(f"[OK] Already normalized: {filename}")
            continue

        final_name = get_available_name(directory, new_name)
        new_path = os.path.join(directory, final_name)

        print(f"[RENAME] {filename}")
        print(f"      -> {final_name}")

        if apply_changes:
            os.rename(old_path, new_path)

    return True


def main():
    if len(sys.argv) < 2:
        print("Usage:")
        print("python rename_finals.py <directory>")
        print("python rename_finals.py <directory> --apply")
        sys.exit(1)

    directory = sys.argv[1]
    apply_changes = "--apply" in sys.argv

    if not apply_changes:
        print("[DRY RUN] No files will be renamed.\n")

    success = rename_finals(
        directory,
        apply_changes=apply_changes
    )

    if not success:
        sys.exit(1)

    if not apply_changes:
        print("\nTo actually rename files, run:")
        print(f"python rename_finals.py {directory} --apply")

    sys.exit(0)


if __name__ == "__main__":
    main()