import os
from datetime import datetime, timedelta
import requests
import logging
import sys

def find_recent_python_files(directory, days):
    cutoff_date = datetime.now() - timedelta(days=days)
    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.endswith(".py"):
                path = os.path.join(root,file)
                try:
                    modified_time = os.path.getmtime(path)
                    modified_date = datetime.fromtimestamp(modified_time)

                    if modified_date >= cutoff_date:
                        print(f"{modified_date}- {path}")
                except OSError:
                    pass
if __name__ == "__main__":
    find_recent_python_files(".", 3)  # Change the directory and days as needed


#funcion para verificar si existe una variable de entorno

def check_environment_variable(variable_name):
    value = os.environ.get(variable_name)
    
    if value:
        print(f"[OK] {variable_name} exists")
    else:
        print(f"[MISSING] {variable_name}")
        sys.exit(1)  # Exit the script with a non-zero status to indicate failure
if __name__ == "__main__":
    check_environment_variable("MY_ENV_VAR")  # Change "MY_ENV_VAR" to the variable you want to check

##USE SYS.EXIT PORQUE EL 0 ME INDICA QUE TODO ESTA BIEN Y EL 1 ME INDICA QUE HAY UN ERROR


## LOGUEAR REQUEST HTTPS FALLIDAS

def setup_logger():
    logging.basicConfig(
        filename="failed_requests.log",
        level=logging.WARNING,
        format= "%(asctime)s - %(levelname)s - %(message)s"

    )


def check_urls_and_log_errors(urls):
    setup_logger()
    for url in urls:
        try:
            response = requests.get(url, timeout=5)
            if response.status_code >=400:
                logging.warning(f"URL={response.url}"
                f"STATUS={response.status_code}"
                f"RESPONSE_TIME = {response.elapsed.total_seconds()}"
                )
            print(f"{url} -> {response.status_code} ")

        except requests.RequestException as error:
            logging.error(
                f"URL={url} ERROR={error}"
            )
if __name__ == "__main__":
    urls_to_check = [
        "https://www.example.com",
        "https://www.nonexistentwebsite.com",
        "https://httpstat.us/404",
        "https://httpstat.us/500"
    ]
    check_urls_and_log_errors(urls_to_check)


#### Show information about user and actual process

def show_process_context():
    print(f"PID: {os.getpid()}")
    print(f"Working directory: {os.getcwd()}")
    print(f"Python executable: {sys.executable}")
    print(f"Arguments: {sys.argv}")

    user = os.environ.get("USER")
    if user:
        print(f"User:{user} ")
    else:
        print("User: unknown")
    if __name__ == "__main__":
        show_process_context()


##detect files with executables permissions

def find_executable_files(directory):
    if not os.path.isdir(directory):
        print(f"[ERROR] Invalid directory: {directory}")
        return None
    executables = []

    for root, dirs, files in os.walk(directory):
        for filename in files:
            path = os.path.join(root,filename)

            try:
                mode = os.stat(path).st_mode
                if mode & stat.S_IXUSR:
                    executables.append(path)
            except OSError as error:
                print(f"[WARNING] Could not access {path}: {error}")

    return executables


    if __name__ == "__main__":
        results = find_executable_files(".")
        if results is None:
            sys.exit(1)
        for path in results:
            print(f"[EXECUTABLE] {path}")
        
        sys.exit(2 if results else 0)  # Exit with 2 if executables found, 0 if none found


#detect   failed logins

def detect_logins_bursts(log_path, threshold = 3, window_seconds=60):
    pattern = re.compile(        r"^(\d{4}-\d{2}-\d{2} "
        r"\d{2}:\d{2}:\d{2}) "
        r"LOGIN_FAILED "
        r"ip=(\d{1,3}(?:\.\d{1,3}){3})")

    attempts_by_ip = {}

    try:
        with open(log_path,"r",encoding = "utf-8",errors = "ignore") as file:
            for line in file:
                match = pattern.search(line)
                if not match:
                    continue
                timestamp = datetime.strptime(match.group(1), "%Y-%m-%d %H:%M:%S")

                ip = match.group(2)

                attempts_by_ip.setdefault(ip, []).append(timestamp)
    
    except OSError as error:
        print(f"[ERROR] Could not read log: {error}")
        return None
    
    alerts = []

    for ip, timestamps in attempts_by_ip.items():
        timestamps.sort()
        for index in range(len(timestamps)):
            start_time = timestamps[index]

            window_end = (start + timedelta(seconds=window_seconds))

            attempts_in_window = (time 
            for time in timestamps
            if start <= time <= window_end)

            if len(attempts_in_window) >= threshold:
                alerts.append({
                    "ip": ip,
                    "attempts": len(attempts_in_window),
                    "window_start": start.isoformat(),
                    "window_seconds": window_seconds

                })
                break
    return alerts
    if __name__ == "__main__":
    alerts = detect_login_bursts(
        "auth.log",
        threshold=3,
        window_seconds=60
    )

    if alerts is None:
        sys.exit(1)

    for alert in alerts:
        print(
            f"[ALERT] IP={alert['ip']} "
            f"ATTEMPTS={alert['attempts']} "
            f"WINDOW={alert['window_seconds']}s"
        )

    sys.exit(2 if alerts else 0)


