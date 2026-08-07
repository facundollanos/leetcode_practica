class Usuario:
    def __init__(self, id , nombre, edad, activo):
        self.id = id
        self.nombre = nombre
        self.edad = edad
        self.activo = activo

usuarios = [Usuario(1, "Alice", 30, True), Usuario(2, "Bob", 25, False)]

for usuario in usuarios:
    print(f"ID: {usuario.id}, Nombre: {usuario.nombre}, Edad: {usuario.edad}, Activo: {usuario.activo
    }")

for usuario in usuarios:
    if usuario.activo:
        print(f"Usuario activo: {usuario.nombre}")
    else:
        print(f"Usuario inactivo: {usuario.nombre}")

