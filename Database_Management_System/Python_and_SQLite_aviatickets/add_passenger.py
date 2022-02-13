import sqlite3

def add_passenger(surname, name, last_name, passport):
    with sqlite3.connect("db.db") as conn:
        cursor = conn.cursor()
        query = """INSERT INTO passengers (surname, name, last_name, passport_number) VALUES (?, ?, ?, ?) """
        data = (surname, name, last_name, passport)
        cursor.execute(query, data)
        conn.commit()
        cursor.close()