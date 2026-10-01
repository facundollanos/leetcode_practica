import os
import stat
import sys



def find_world_writable(directory):
    findings = []

    for root, _, files in os.walk(directory):
        for filename in files:
            path = os.path.join(root, filename)

            try:
                info = os.lstat(path)

            except OSError:
                continue

            if stat.S_ISLNK(info.st_mode):
                continue

            if info.st_mode & stat.S_IWOTH:
                findings.append({
                    "path": path,
                    "mode": stat.filemode(
                        info.st_mode
                    )
                })

    return findings


def main():
    if len(sys.argv) != 2:
        print(
            "Usage: python3 writable.py "
            "<directory>"
        )
        sys.exit(1)

    directory = sys.argv[1]

    if not os.path.isdir(directory):
        print("[ERROR] Invalid directory")
        sys.exit(1)

    findings = find_world_writable(
        directory
    )

    for item in findings:
        print(
            f"[REVIEW] "
            f"{item['mode']} "
            f"{item['path']}"
        )

    print(
        f"\nWorld-writable files: "
        f"{len(findings)}"
    )

    sys.exit(2 if findings else 0)


if __name__ == "__main__":
    main()


#linux uptime checker


UPTIME_FILE = "/proc/uptime"


def get_uptime():
    try:
        with open(
            UPTIME_FILE,
            "r",
            encoding="utf-8"
        ) as file:

            first = file.read().split()[0]

            return float(first)

    except (
        OSError,
        ValueError,
        IndexError
    ):
        return None


def format_uptime(seconds):
    total = int(seconds)

    days, total = divmod(
        total,
        86400
    )

    hours, total = divmod(
        total,
        3600
    )

    minutes, seconds = divmod(
        total,
        60
    )

    return (
        f"{days}d "
        f"{hours}h "
        f"{minutes}m "
        f"{seconds}s"
    )


def main():
    if not sys.platform.startswith(
        "linux"
    ):
        print("[ERROR] Linux required")
        sys.exit(1)

    if not os.path.isfile(
        UPTIME_FILE
    ):
        print(
            "[ERROR] /proc/uptime unavailable"
        )
        sys.exit(1)

    uptime = get_uptime()

    if uptime is None:
        print(
            "[ERROR] Could not read uptime"
        )
        sys.exit(1)

    print(
        f"Uptime: "
        f"{format_uptime(uptime)}"
    )

    if uptime < 300:
        print(
            "[INFO] System booted "
            "less than 5 minutes ago"
        )


if __name__ == "__main__":
    main()