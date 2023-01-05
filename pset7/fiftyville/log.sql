-- Keep a log of any SQL queries you execute as you solve the mystery.


SELECT description FROM crime_scene_reports WHERE day = 28 AND month = 7 AND street = "Humphrey Street";
--The above command reveals that there were 3 witnesses, and the crime took place at 10:15 AM at the Humphrey Street Bakery

SELECT transcript FROM interviews WHERE month = 7 AND day = 28;
--The above command reveals that
--1) The thief used an ATM at Leggett Street that morning
--2) The thief was planning to take the earliest flight out of fiftyville the next day
--3) The thief made a phone call to a person for less than a minute when leaving the bakery telling them to book the ticket
--4) The thief left within 10 minutes of the theft
--5) Someone came in whispering into a phone for 30 minutes and did not buy anything

SELECT caller, receiver FROM phone_calls WHERE month = 7 AND day = 28 AND duration < 60;

SELECT origin_airport_id, destination_airport_id, full_name, city, flights.id, flights.hour, flights.minute
    FROM flights
    INNER JOIN airports
    ON flights.destination_airport_id = airports.id
    WHERE flights.day = 29
    AND flights.month = 7
    AND flights.year = 2021
    ORDER BY flights.hour, flights.minute;
--A flight with ID 36 left first thing in the morning to Dallas/Fort Worth International Airport carrying the thief

SELECT DISTINCT people.phone_number, people.name
    FROM people
    INNER JOIN passengers
    ON people.passport_number = passengers.passport_number
    INNER JOIN phone_calls
    ON phone_calls.caller = people.phone_number
    WHERE passengers.flight_id = 36
    AND phone_calls.duration < 1
    AND phone_calls.month = 7
    AND phone_calls.day = 28;



SELECT DISTINCT name
    FROM phone_calls
    INNER JOIN people
    ON phone_calls.caller = people.phone_number
    WHERE receiver = "(066) 555-9701"
    AND phone_calls.day = 28
    AND phone_calls.duration < 60;


SELECT MAX(duration)
    FROM phone_calls
    INNER JOIN people
    ON phone_calls.caller = people.phone_number
    WHERE duration > 1500
    AND phone_calls.day = 28
    AND phone_calls.duration = 7;


SELECT MAX(duration)
    FROM phone_calls


SELECT DISTINCT name, b.license_plate, people.passport_number, people.phone_number
    FROM bakery_security_logs AS b
    INNER JOIN people
    ON people.license_plate = b.license_plate
    WHERE b.day = 28
    AND b.month = 7
    AND b.year = 2021
    AND b.hour = 10
    AND b.minute BETWEEN 15 AND 25
    AND b.activity = "exit";

CREATE TABLE suspect_table AS
    SELECT DISTINCT name, b.license_plate, people.passport_number, people.phone_number, people.id
    FROM bakery_security_logs AS b
    INNER JOIN people
    ON people.license_plate = b.license_plate
    WHERE b.day = 28
    AND b.month = 7
    AND b.year = 2021
    AND b.hour = 10
    AND b.minute BETWEEN 15 AND 25
    AND b.activity = "exit";


SELECT suspect_table.name, suspect_table.phone_number
    FROM suspect_table
    INNER JOIN bank_accounts
    ON bank_accounts.person_id = suspect_table.id
    INNER JOIN atm_transactions
    ON bank_accounts.account_number = atm_transactions.account_number
    WHERE atm_transactions.atm_location = "Leggett Street"
    AND atm_transactions.day = 28
    AND atm_transactions.month = 7
    AND atm_transactions.year = 2021;


SELECT name FROM phone_calls
    INNER JOIN people
    ON phone_calls.receiver = people.phone_number
    WHERE phone_calls.caller = "(367) 555-5533"
    AND duration < 60
    AND day = 28
    AND month = 7
    AND year = 2021;