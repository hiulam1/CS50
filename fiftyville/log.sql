-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Checking the crime scene report of the day of theft
SELECT description
FROM crime_scene_reports
WHERE month = 7
AND day = 28
AND year = 2021;

-- Theft of duck took place at 10:15am Humphrey Street Bakery. Interviews with 3 witnesses, interviews mention the bakery.

-- Checking the transcripts of the interviews on day of theft.
SELECT transcript, name
FROM interviews
WHERE month = 7
AND day = 28
AND year = 2021
AND transcript LIKE '%bakery%';

-- Within 10 mins of theft, the thief got into a car in the bakery parking lot and drove away. The thief was trying to book a flight the next day (29.07.2021). The thief may know Eugene.
-- Check bakery shop security footage at roughly 10:25am.
-- Thief called someone


SELECT bakery_security_logs.license_plate, people.name
FROM bakery_security_logs
    JOIN people ON people.license_plate = bakery_security_logs.license_plate
    WHERE bakery_security_logs.month = 7
    AND bakery_security_logs.day = 28
    AND bakery_security_logs.year = 2021
    AND bakery_security_logs.hour = 10
    AND bakery_security_logs.minute between 10 AND 20
    AND bakery_security_logs.activity = 'exit';

-- Check ATM on Leggett Street in the morning of the crime.
SELECT people.name FROM people
    JOIN bank_accounts on people.id = bank_accounts.person_id
        JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
        WHERE atm_transactions.atm_location = 'Leggett Street'
        AND atm_transactions.transaction_type = 'withdraw'
        AND atm_transactions.year = 2021
        AND atm_transactions.month = 7
        AND atm_transactions.day = 28;

-- Check Eugene from People
SELECT * FROM people WHERE name = 'Eugene';

-- phone number = (666) 555-5774; passport_number: 9584465633; license_place: 47592FJ;

-- Check phone logs
SELECT people.name, phone_calls.duration FROM people
    JOIN phone_calls on phone_calls.caller = people.phone_number
    WHERE phone_calls.year = 2021
    AND phone_calls.month = 7
    AND phone_calls.day = 28;
    AND phone_calls.duration <= 60;


-- Finding the person who matches the description of the three witness testimonies as well as who boarded the earliest flight on the next day.
SELECT people.name, people.passport_number
FROM people
-- checking bakery security logs where cars exited between 10:20am and 10:30am
    JOIN bakery_security_logs
    ON bakery_security_logs.license_plate = people.license_plate
    WHERE bakery_security_logs.month = 7
    AND bakery_security_logs.day = 28
    AND bakery_security_logs.year = 2021
    AND bakery_security_logs.hour = 10
    AND bakery_security_logs.minute between 10 AND 20
    AND bakery_security_logs.activity = 'exit'
    AND people.id IN
    (
        SELECT bank_accounts.person_id
        FROM bank_accounts
            JOIN atm_transactions
            ON atm_transactions.account_number = bank_accounts.account_number
            WHERE atm_transactions.atm_location = 'Leggett Street'
            AND atm_transactions.transaction_type = 'withdraw'
            AND atm_transactions.year = 2021
            AND atm_transactions.month = 7
            AND atm_transactions.day = 28
    )
    AND people.phone_number IN
    (
        SELECT phone_calls.caller
        FROM phone_calls
        WHERE year = 2021
        AND month = 7
        AND day = 28
    );


-- Finding accomplice using phone logs
SELECT people.name
FROM people
    JOIN phone_calls
    ON phone_calls.receiver = people.phone_number
    WHERE phone_calls.year = 2021
    AND phone_calls.month = 7
    AND phone_calls.day = 28
    AND phone_calls.duration <= 60
    AND phone_calls.caller IN
        (
            SELECT people.phone_number
            FROM people
            where people.name = 'Bruce'
        );

-- Finding city that Bruce fled to
SELECT airports.city
FROM airports
    JOIN flights
    ON flights.destination_airport_id = airports.id
    WHERE flights.origin_airport_id
    IN
        (
            SELECT airports.id
            FROM airports
            WHERE airports.full_name LIKE 'Fiftyville%'
        )
    AND flights.year = 2021
    AND flights.month = 7
    AND flights.day = 29
    AND flights.hour = 8
    AND flights.minute= 20;