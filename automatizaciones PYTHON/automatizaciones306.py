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


