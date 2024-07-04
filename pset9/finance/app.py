import os
import time
import re
from datetime import date
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
# Configure date and time
t = time.localtime()
time_now = time.strftime("%H:%M:%S", t)
date_today = date.today()

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")
t = time.localtime()
# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # stocks user own , number of shares owned, current price ,total value, current cash balance
    TotalBalance = db.execute("Select cash from users where id = ?", session["user_id"])[0]['cash']
    sharesDict = {}
    currentPriceDict = {}
    totValDict = {}
    i = 0
    stocks = db.execute("SELECT DISTINCT symbol FROM purchases where user_id = ?", session["user_id"])
    for stock in stocks:
        shares = db.execute("SELECT SUM(shares) from purchases where symbol = ? AND user_id = ?",
                            stock['symbol'], session["user_id"])
        sharesDict[i] = shares[0]['SUM(shares)']
        currentPrice = lookup(stock['symbol'])['price']
        currentPriceDict[i] = currentPrice
        totVal = currentPrice * shares[0]['SUM(shares)']
        totValDict[i] = totVal
        TotalBalance += totVal
        i = i + 1
    print(sharesDict, currentPriceDict, totValDict)
    return render_template("index.html", stocks=range(len(stocks)),
                           symbol=stocks, shares=sharesDict, currentPrice=currentPriceDict, totVal=totValDict,
                           TotalBalance=usd(TotalBalance),)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    payment = 0
    user_money = 0
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares_NR = request.form.get("shares")

        if not request.form.get("symbol") or lookup(symbol) == None:
            return apology("Invalid symbol", 400)
        elif not shares_NR.isnumeric():
            return apology("Invalid Number of Shares", 400)
        elif int(shares_NR) < 0:
            return apology("Invalid Number of Shares", 400)

        share_info = lookup(symbol)
        price_per_share = lookup(symbol)['price']
        user_money = db.execute("SELECT cash from users where id = ?", session["user_id"])[0]['cash']

        if price_per_share * float(shares_NR) > user_money:
            return apology("Not enough money", 400)
        else:
            user_money = user_money - (price_per_share * float(shares_NR))
            payment = price_per_share * float(shares_NR)
            db.execute("INSERT INTO purchases (user_id,shares,name,price,symbol,date,hour) VALUES (?,?,?,?,?,?,?)",
                       session["user_id"], int(shares_NR), share_info['name'], share_info['price'], share_info['symbol'], date_today, time_now)
            db.execute("UPDATE users SET cash = ? WHERE ID = ?", user_money, session["user_id"])

    return render_template("buy.html", payment=payment, user_money=user_money)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    PurchasesDict = db.execute("SELECT name,symbol,price,shares,date,hour from purchases where user_id = ?", session['user_id'])
    SalesDict = db.execute("SELECT name,symbol,price,shares,date,hour from sales where user_id = ?", session['user_id'])
    print(len(PurchasesDict))
    return render_template("history.html", lenSales=range(len(SalesDict)), lenPurchases=range(len(PurchasesDict)), sales=SalesDict, purchases=PurchasesDict)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/reset", methods=["GET", "POST"])
@login_required
def reset():
    """Reset password"""
    if request.method == "POST":
        oldPass = request.form.get("oldPassword")
        newPass = request.form.get("newPassword")
        confirmNewPass = request.form.get("newPassConfirmation")
        validate = db.execute("SELECT * FROM users WHERE id = ?", session['user_id'])
        if not check_password_hash(validate[0]["hash"], oldPass) or not request.form.get("oldPassword"):
            return apology("invalid old password", 403)
        elif not request.form.get("newPassword"):
            return apology("Invalid new password", 403)
        elif not newPass == confirmNewPass:
            return apology("Confirmation password don't match", 403)
        else:
            db.execute("UPDATE users SET hash = ? WHERE ID = ?", generate_password_hash(newPass), session['user_id'])
    return render_template("reset.html")


@app.route("/addCash", methods=["GET", "POST"])
@login_required
def addCash():
    """add cahs to account"""
    if request.method == "POST":
        addCash = request.form.get("addCash")
        getMoney = db.execute("SELECT cash from users where id = ?", session['user_id'])[0]['cash']
        if not request.form.get("addCash") or not addCash.isnumeric() or int(addCash) < 0:
            return apology("Invalid number", 400)
        else:
            db.execute("UPDATE users SET cash = ? where id = ?", getMoney+float(addCash), session['user_id'])
    return render_template("addCash.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    price = 0
    if request.method == "POST":
        symbol = request.form.get("symbol")
        info = lookup(symbol)
        if not request.form.get("symbol") or info == None:
            return apology("Invalid Symbol", 400)
        else:
            price = float(info['price'])
            return render_template("quoted.html", info=info, price=price)

    return render_template("quote.html", price=price)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        name = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        nameValidation = db.execute("SELECT username from users WHERE username = ?", name)
        if not request.form.get("username"):
            return apology("must provide username", 400)
        elif not len(nameValidation) == 0:
            return apology("username already in use", 400)
        elif not request.form.get("password"):
            return apology("must provide password", 400)
        elif not request.form.get("confirmation"):
            return apology("must confirm password", 400)
        elif len(password) < 6:
            return apology("password is shorter than 6 characters", 400)
        elif not re.findall("^[A-Z]", password):
            return apology("password doesn't start with uppercase letter", 400)
        elif not re.findall("\d", password):
            return apology("password doesn't containt numbers", 400)
        elif not re.findall("[!@#$%^&*]", password):
            return apology("password doesn't contain special symbols", 400)

        if not(password == confirmation):
            return apology("password don't match", 400)
        else:
            hashedPS = generate_password_hash(password)
            db.execute("INSERT INTO USERS (username,hash) VALUES (?,?)", name, hashedPS)

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_money = 0
    check = 0
    stocks = db.execute("SELECT DISTINCT symbol FROM purchases where user_id = ?", session["user_id"])
    if request.method == "POST":
        share_name = request.form.get("symbol")
        shareNR = request.form.get("shares", type=int)
        shareNRvalidate = db.execute("SELECT SUM(shares) from purchases where symbol = ? AND user_id = ?",
                                     share_name, session["user_id"])
        user_money = db.execute("SELECT cash from users where id = ?", session["user_id"])[0]['cash']
        price_per_share = lookup(share_name)['price']
        share_info = lookup(share_name)
        share_name_validate = db.execute(
            "SELECT DISTINCT symbol from purchases where symbol = ? and user_id = ?", share_name, session["user_id"])
        print(share_name_validate)
        if not request.form.get("symbol") or not len(share_name_validate) == 1:
            return apology("Invalid Stock", 400)
        elif not request.form.get("shares") or shareNR < 0 or shareNRvalidate[0]['SUM(shares)'] == 0 or shareNR > shareNRvalidate[0]['SUM(shares)']:
            return apology("Invalid number of shares", 400)
        else:
            user_money = user_money + (price_per_share * shareNR)
            check = price_per_share * shareNR
            db.execute("INSERT INTO sales (user_id,shares,name,price,symbol,date,hour) VALUES (?,?,?,?,?,?,?)",
                       session["user_id"], shareNR, share_info['name'], share_info['price'], share_info['symbol'], date_today, time_now)
            db.execute("UPDATE users SET cash = ? WHERE ID = ?", user_money, session["user_id"])
    return render_template("sell.html", stocks=stocks, user_money=user_money, check=check)