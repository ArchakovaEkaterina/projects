import sqlite3

def Test():
    with sqlite3.connect("db.db") as conn:
        cursor = conn.cursor()
        query = """SELECT passengers.surname, passengers.name, passengers.last_name,
        passengers.passport FROM passengers"""
        cursor.execute(query)