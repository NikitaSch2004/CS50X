-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT * FROM CRIME_SCENE_REPORTS WHERE street =  "Humphrey Street";
/*| 295 | 2021 | 7     | 28  | Humphrey Street | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |*/

SELECT * from interviews where year = 2021 and month = 7 and day = 28;
/*| 161 | Ruth    | 2021 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
| 162 | Eugene  | 2021 | 7     | 28  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery,
 I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
| 163 | Raymond | 2021 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call,
I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of
the phone to purchase the flight ticket. |*/

SELECT * FROM bakery_security_logs where year = 2021 and month = 7 and day = 28 and hour = 10 and minute between 5 and 25;
/*| 260 | 2021 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
| 261 | 2021 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
| 262 | 2021 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
| 263 | 2021 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
| 264 | 2021 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
| 265 | 2021 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
| 266 | 2021 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
| 267 | 2021 | 7     | 28  | 10   | 23     | exit     | 0NTHK55 */

SELECT * FROM atm_transactions where year = 2021 and month = 7 and day = 28 and atm_location like ("Leggett Street");
/*246 | 28500762       | 2021 | 7     | 28  | Leggett Street | withdraw         | 48     |
| 264 | 28296815       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 266 | 76054385       | 2021 | 7     | 28  | Leggett Street | withdraw         | 60     |
| 267 | 49610011       | 2021 | 7     | 28  | Leggett Street | withdraw         | 50     |
| 269 | 16153065       | 2021 | 7     | 28  | Leggett Street | withdraw         | 80     |
| 288 | 25506511       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
| 313 | 81061156       | 2021 | 7     | 28  | Leggett Street | withdraw         | 30     |
| 336 | 26013199       | 2021 | 7     | 28  | Leggett Street | withdraw         | 35     |*/

SELECT * FROM phone_calls  where year = 2021 and month = 7 and day = 28 and duration < 60;
/*221 | (130) 555-0289 | (996) 555-8899 | 2021 | 7     | 28  | 51       |
| 224 | (499) 555-9472 | (892) 555-8872 | 2021 | 7     | 28  | 36       |
| 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |
| 251 | (499) 555-9472 | (717) 555-1342 | 2021 | 7     | 28  | 50       |
| 254 | (286) 555-6063 | (676) 555-6554 | 2021 | 7     | 28  | 43       |
| 255 | (770) 555-1861 | (725) 555-3243 | 2021 | 7     | 28  | 49       |
| 261 | (031) 555-6622 | (910) 555-3251 | 2021 | 7     | 28  | 38       |
| 279 | (826) 555-1652 | (066) 555-9701 | 2021 | 7     | 28  | 55       |
| 281 | (338) 555-6650 | (704) 555-2131 | 2021 | 7     | 28  | 54       |*/

SELECT * FROM BANK_ACCOUNTS WHERE account_number in
(SELECT account_number FROM atm_transactions where year = 2021 and month = 7 and day = 28 and atm_location like ("Leggett Street"));
/*| 49610011       | 686048    | 2010          |
| 86363979       | 948985    | 2010          |
| 26013199       | 514354    | 2012          |
| 16153065       | 458378    | 2012          |
| 28296815       | 395717    | 2014          |
| 25506511       | 396669    | 2014          |
| 28500762       | 467400    | 2014          |
| 76054385       | 449774    | 2015          |
| 81061156       | 438727    | 2018          |*/

SELECT * FROM people where id in (SELECT person_id FROM BANK_ACCOUNTS WHERE account_number in
(SELECT account_number FROM atm_transactions where year = 2021 and month = 7 and day = 28 and atm_location like ("Leggett Street")))
AND phone_number in (SELECT caller FROM phone_calls  where year = 2021 and month = 7 and day = 28 and duration < 60)
AND license_plate in (SELECT license_plate FROM bakery_security_logs where year = 2021 and month = 7 and day = 28 and hour = 10 and minute between 5 and 25);
/*| 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
| 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |*/

SELECT * FROM passengers WHERE passport_number in (SELECT passport_number FROM people where id in (SELECT person_id FROM BANK_ACCOUNTS WHERE account_number in
(SELECT account_number FROM atm_transactions where year = 2021 and month = 7 and day = 28 and atm_location like ("Leggett Street")))
AND phone_number in (SELECT caller FROM phone_calls  where year = 2021 and month = 7 and day = 28 and duration < 60)
AND license_plate in (SELECT license_plate FROM bakery_security_logs where year = 2021 and month = 7 and day = 28 and hour = 10 and minute between 5 and 25));
/*| 18        | 3592750733      | 4C   |
| 24        | 3592750733      | 2C   |
| 36        | 5773159633      | 4A   |
| 54        | 3592750733      | 6C   |*/

SELECT * from people where phone_number in (SELECT receiver from phone_calls where caller in (SELECT phone_number FROM people where id in
(SELECT person_id FROM BANK_ACCOUNTS WHERE account_number in
(SELECT account_number FROM atm_transactions where year = 2021 and month = 7 and day = 28 and atm_location like ("Leggett Street")))
AND phone_number in (SELECT caller FROM phone_calls  where year = 2021 and month = 7 and day = 28 and duration < 60)
AND license_plate in (SELECT license_plate FROM bakery_security_logs where year = 2021 and month = 7 and day = 28 and hour = 10 and minute between 5 and 25)) and year = 2021
and month = 7 and day = 28 and duration < 60);
/*| 847116 | Philip | (725) 555-3243 | 3391710505      | GW362R6       |
| 864400 | Robin  | (375) 555-8161 |                 | 4V16VO0       |*/

SELECT * FROM passengers where passport_number in (SELECT passport_number from people where phone_number in (SELECT receiver from phone_calls where caller in (SELECT phone_number FROM people where id in
(SELECT person_id FROM BANK_ACCOUNTS WHERE account_number in
(SELECT account_number FROM atm_transactions where year = 2021 and month = 7 and day = 28 and atm_location like ("Leggett Street")))
AND phone_number in (SELECT caller FROM phone_calls  where year = 2021 and month = 7 and day = 28 and duration < 60)
AND license_plate in (SELECT license_plate FROM bakery_security_logs where year = 2021 and month = 7 and day = 28 and hour = 10 and minute between 5 and 25)) and year = 2021
and month = 7 and day = 28 and duration < 60));
/*| 10        | 3391710505      | 2A   |
| 28        | 3391710505      | 2A   |
| 47        | 3391710505      | 4D   |*/

SELECT * from flights where id in (SELECT flight_id FROM passengers where passport_number in (SELECT passport_number from people where phone_number in (SELECT receiver from phone_calls where caller in (SELECT phone_number FROM people where id in
(SELECT person_id FROM BANK_ACCOUNTS WHERE account_number in
(SELECT account_number FROM atm_transactions where year = 2021 and month = 7 and day = 28 and atm_location like ("Leggett Street")))
AND phone_number in (SELECT caller FROM phone_calls  where year = 2021 and month = 7 and day = 28 and duration < 60)
AND license_plate in (SELECT license_plate FROM bakery_security_logs where year = 2021 and month = 7 and day = 28 and hour = 10 and minute between 5 and 25)) and year = 2021
and month = 7 and day = 28 and duration < 60)));
/*| 10 | 8                 | 4                      | 2021 | 7     | 30  | 13   | 55     |
| 28 | 3                 | 8                      | 2021 | 7     | 26  | 22   | 49     |
| 47 | 4                 | 8                      | 2021 | 7     | 30  | 9    | 46     |*/


SELECT * FROM FLIGHTS WHERE ID in (SELECT flight_id FROM passengers WHERE passport_number in (SELECT passport_number FROM people where id in (SELECT person_id FROM BANK_ACCOUNTS WHERE account_number in
(SELECT account_number FROM atm_transactions where year = 2021 and month = 7 and day = 28 and atm_location like ("Leggett Street")))
AND phone_number in (SELECT caller FROM phone_calls  where year = 2021 and month = 7 and day = 28 and duration < 60)
AND license_plate in (SELECT license_plate FROM bakery_security_logs where year = 2021 and month = 7 and day = 28 and hour = 10 and minute between 5 and 25)));
/*| 18 | 8                 | 6                      | 2021 | 7     | 29  | 16   | 0      |
| 24 | 7                 | 8                      | 2021 | 7     | 30  | 16   | 27     |
| 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     |
| 54 | 8                 | 5                      | 2021 | 7     | 30  | 10   | 19     |*/

SELECT * FROM airports where id in (SELECT origin_airport_id FROM FLIGHTS WHERE ID in (SELECT flight_id FROM passengers WHERE passport_number in (SELECT passport_number FROM people where id in (SELECT person_id FROM BANK_ACCOUNTS WHERE account_number in
(SELECT account_number FROM atm_transactions where year = 2021 and month = 7 and day = 28 and atm_location like ("Leggett Street")))
AND phone_number in (SELECT caller FROM phone_calls  where year = 2021 and month = 7 and day = 28 and duration < 60)
AND license_plate in (SELECT license_plate FROM bakery_security_logs where year = 2021 and month = 7 and day = 28 and hour = 10 and minute between 5 and 25))));
/*| 7  | DXB          | Dubai International Airport | Dubai      |
| 8  | CSF          | Fiftyville Regional Airport | Fiftyville |*/

SELECT * FROM airports where id in (SELECT destination_airport_id FROM FLIGHTS WHERE ID in (SELECT flight_id FROM passengers WHERE passport_number in (SELECT passport_number FROM people where id in (SELECT person_id FROM BANK_ACCOUNTS WHERE account_number in
(SELECT account_number FROM atm_transactions where year = 2021 and month = 7 and day = 28 and atm_location like ("Leggett Street")))
AND phone_number in (SELECT caller FROM phone_calls  where year = 2021 and month = 7 and day = 28 and duration < 60)
AND license_plate in (SELECT license_plate FROM bakery_security_logs where year = 2021 and month = 7 and day = 28 and hour = 10 and minute between 5 and 25))));
/*| 4  | LGA          | LaGuardia Airport                       | New York City |
| 5  | DFS          | Dallas/Fort Worth International Airport | Dallas        |
| 6  | BOS          | Logan International Airport             | Boston        |
| 8  | CSF          | Fiftyville Regional Airport             | Fiftyville    |*/