import sqlite3

def select_passenger(surname, name, last_name, passport):
    with sqlite3.connect("db.db") as conn:
        cursor = conn.cursor()
        query = """SELECT * 
                FROM passengers 
                WHERE passport_number="%s" AND surname="%s" AND name="%s" AND last_name="%s" """ \
                % (passport, surname, name, last_name)
        result = cursor.execute(query).fetchall()
        cursor.close()
        return result