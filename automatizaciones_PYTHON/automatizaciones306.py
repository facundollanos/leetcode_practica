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



SECURITY_HEADERS  = {

    "Strict-Transport-Security:":
        "Enforces HTTPS usage",
    "Content-Security-Policy":
        "Restricts permitted content sources",
    "X-Content-Type-Options":
        "Prevents MIME type sniffing"
}

def basicAuditHTTPsecurity(url):
    try:
        response = requests.get(
            url,timeot=6, allow_redirects = True,
            headers={"User-Agent": "Python-Security-Header-Audit/1.0"}

        )

    except requests.RequestException as error:
        print(f"[ERROR] Request failed for {url}: {error}")
        return None
    except requests.Timeout:
        print(f"[ERROR] Request timed out for {url}")
        return None

    findings =[]
    present_count=0

    for header, description in (SECURITY_HEADERS.items()):
        value = response.headers.get(header)
        if value:
            present_count+= 1
            findings.append({
                "header": header,
                "description": description,
                "value": value,
                "present": True
            })
        else:
            findings.append({
                "header": header,
                "present": False,
                "value": None,
                "description": description
            })
    score = round(present_count / len(SECURITY_HEADERS) * 100)

    return {
        "url": url,
        "score": score,
        "findings": findings,
        "final_url": response.url,
        "status_code": response.status_code

    }
    if __name__ == "__main__":
    url = (
        sys.argv[1]
        if len(sys.argv) == 2
        else "https://github.com"
    )

    result = audit_security_headers(url)

    if result is None:
        sys.exit(1)

    print(f"URL: {result['final_url']}")
    print(f"Status: {result['status_code']}")
    print(f"Security header score: {result['score']}%\n")

    for finding in result["findings"]:
        if finding["present"]:
            print(
                f"[PRESENT] "
                f"{finding['header']}"
            )
            print(
                f"  Value: {finding['value']}"
            )
        else:
            print(
                f"[MISSING] "
                f"{finding['header']}"
            )

        print(
            f"  Purpose: "
            f"{finding['description']}"
        )

    missing = [
        finding
        for finding in result["findings"]
        if not finding["present"]
    ]

    sys.exit(2 if missing else 0)



    import json
import os
import sys
from concurrent.futures import (
    ThreadPoolExecutor,
    as_completed
)



#####
8
from datetime import datetime, timezone

import requests


def check_endpoint(url, timeout):
    checked_at = datetime.now(
        timezone.utc
    ).isoformat()

    try:
        response = requests.get(
            url,
            timeout=timeout,
            allow_redirects=True,
            headers={
                "User-Agent":
                    "Python-Concurrent-Monitor/1.0"
            }
        )

        response_time = (
            response.elapsed.total_seconds()
        )

        if response.status_code >= 500:
            state = "server_error"

        elif response.status_code >= 400:
            state = "client_error"

        elif response_time > 2:
            state = "slow"

        else:
            state = "healthy"

        return {
            "url": url,
            "final_url": response.url,
            "status_code": response.status_code,
            "response_time_seconds": round(
                response_time,
                4
            ),
            "state": state,
            "checked_at": checked_at
        }

    except requests.Timeout:
        return {
            "url": url,
            "state": "timeout",
            "checked_at": checked_at
        }

    except requests.ConnectionError as error:
        return {
            "url": url,
            "state": "connection_error",
            "error": str(error),
            "checked_at": checked_at
        }

    except requests.RequestException as error:
        return {
            "url": url,
            "state": "request_error",
            "error": str(error),
            "checked_at": checked_at
        }


def monitor_endpoints(
    urls,
    timeout=5,
    max_workers=5
):
    results = []

    with ThreadPoolExecutor(
        max_workers=max_workers
    ) as executor:

        future_to_url = {
            executor.submit(
                check_endpoint,
                url,
                timeout
            ): url
            for url in urls
        }

        for future in as_completed(
            future_to_url
        ):
            url = future_to_url[future]

            try:
                result = future.result()

            except Exception as error:
                result = {
                    "url": url,
                    "state": "internal_error",
                    "error": str(error)
                }

            results.append(result)

    return sorted(
        results,
        key=lambda item: item["url"]
    )


def save_report(results, path):
    directory = os.path.dirname(path)

    if directory:
        os.makedirs(
            directory,
            exist_ok=True
        )

    report = {
        "generated_at": datetime.now(
            timezone.utc
        ).isoformat(),
        "service_count": len(results),
        "results": results
    }

    try:
        with open(
            path,
            "w",
            encoding="utf-8"
        ) as file:
            json.dump(
                report,
                file,
                indent=4
            )

    except OSError as error:
        print(
            f"[ERROR] Could not save report: "
            f"{error}"
        )
        return False

    return True


if __name__ == "__main__":
    endpoints = [
        "https://api.github.com",
        "https://example.com",
        "https://httpbin.org/status/404",
        "https://httpbin.org/status/503",
        "https://httpbin.org/delay/2"
    ]

    results = monitor_endpoints(
        urls=endpoints,
        timeout=5,
        max_workers=5
    )

    for result in results:
        print(
            f"[{result['state'].upper()}] "
            f"{result['url']} "
            f"STATUS="
            f"{result.get('status_code', 'N/A')} "
            f"TIME="
            f"{result.get('response_time_seconds', 'N/A')}"
        )

    if not save_report(
        results,
        "reports/concurrent_monitor.json"
    ):
        sys.exit(1)

    unhealthy = [
        result
        for result in results
        if result["state"] not in {
            "healthy",
            "slow"
        }
    ]

    sys.exit(2 if unhealthy else 0)





def detect_zombies_process():
    if sys.platform != "linux":
        print("[ERROR] This script requieres Linux.")
        return None
    zombies = []
    for entry in os.listdir("/proc"):
        if not entry.isdigit():
            continue
        pid = entry
        status_path = f"/proc/{pid}/status"
        try:
            with open(status_path,"r", encoding="utf-8")as file:
                process_data = {}
                for line in file:
                    key,separator,value = line.partition(":")
                    if separator:
                        process_data[key] = value.strip()
        except OSError:
            continue
        state = process_data.get("State","")
        if state.startswith("Z"):
            zombies.append({
                "pid": int(pid),
                "name": process_data.get(
                    "Name", "unknown"
                ),
                "state": state
            })
    return zombies

if __name__ == "__main__":
    zombies = detect_zombies_process()
    if zombies is None:
        sys.exit(1)

    for process in zombies:
        print(
            f"[ZOMBIE] "
            f"PID = {process['pid']}"
            f"NAME = {process['name']}"
            f"PPID = {process[parent_pid]}"
            f"STATE = {process['state']}"
        )