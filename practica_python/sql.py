import sqlite3
conexion = sqlite3.connect("practica_python.db")
cursor = conexion.cursor()

usuarios = [("Ana",25,1),("Luis",30,0),("Marta",28,1)]
cursor.executemany("INSERT INTO usuarios (nombre,edad,activo) VALUES (?,?,?)", usuarios)

