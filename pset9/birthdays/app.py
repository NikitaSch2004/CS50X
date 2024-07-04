import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")
Dict= {}

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database
        name = request.form.get("name")
        day = request.form.get("day")
        month = request.form.get("month")
        if name == "" or day == "" or month == "":
            return redirect("/")
        elif not(day >= 1 and day <= 31) or not(month >= 1 and month <= 12):
            return redirect("/")
        else:
            print(name,day,month)
            db.execute("INSERT INTO BIRTHDAYS (name,month,day) VALUES (?,?,?)",name,month,day)
            return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        Dict = db.execute("SELECT name,month,day from birthdays")
        return render_template("index.html", Dict=Dict)


