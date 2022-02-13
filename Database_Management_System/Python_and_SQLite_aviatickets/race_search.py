import sqlite3

def race_search(date_out, point_out, point_in):
    with sqlite3.connect("db.db") as conn:
        cursor = conn.cursor()
        query = """SELECT races.race_number, races.date_out, races.time_out, races.time_in, 
        races.point_out, races.point_in, races.id
        FROM races
        WHERE races.date_out="%s" AND races.point_out="%s" AND races.point_in="%s" """ % (date_out, point_out, point_in)
        result = cursor.execute(query).fetchall()
        cursor.close()
        return result