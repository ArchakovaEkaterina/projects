import sqlite3

def class_places(place_class, id_race):
    with sqlite3.connect("db.db") as conn:
        cursor = conn.cursor()
        query = """SELECT tickets.place_number
        FROM tickets
        WHERE tickets.place_class="%s" AND tickets.id_race="%s" """ % (place_class, id_race)
        cursor.execute(query)