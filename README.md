# Project-1 — QParking

CSCE 2110 Group 8

Members: Zachary Yandell, Nicholas Richburg (Our other group member has not reached out to us)

QParking simulates a valet parking operation with m stack (LIFO) garages of capacity n.
The most recently parked car sits on top, so retrieving a buried car means temporarily
moving the cars above it — which is always possible because n spaces (marked `R`) stay
reserved, capping the lot at n×(m−1) cars. See `QParking_Project_Design.docx` for the
full design.

## How to compile

Make sure all files are located in the same directory. In the terminal type:

```sh
g++ main.cpp customer.cpp garage.cpp qparking.cpp
```

(Compiles clean with `-Wall -Wextra` as well.)

## How to run

```sh
./a.out config.txt        (./a.exe config.txt on Windows)
```

Or run with no argument and type the config file name at the prompt. The program loads
the configuration, runs the interactions, prints the final lot status, and writes the
final occupancy grid to `output.txt`.

## Input files

- **config.txt** — line 1: `<numGarages> <capacity>`; line 2: occupancy file name;
  line 3: customers file name; line 4 (optional): interactions file name.
- **occupancy.csv** — the starting grid. Each **column** is a garage, each row a spot.
  Cells: `-1` free, `R` reserved (never assigned), or a customer id. The last row is
  the **bottom** of each stack; cars fill upward.
- **customers.csv** — one customer per row: `name, phone, arrival, departure`.
  Customers are assigned ids 1, 2, 3, ... in file order.
- **interactions.txt** — one interaction per line, executed in order:
  - `D: name, phone, time` — a new customer drops off a car (gets the next id and a spot)
  - `P: customerID` — a customer picks up their car (cars stacked above it are moved
    aside and restacked in order)

## Files / components

| File | Contents |
| --- | --- |
| `main.cpp` | Driver: load config → run interactions → print status → write output.txt |
| `qparking.h/.cpp` | `QParkingSystem` controller: config loading (C1), interaction processing (C2), parking assignment (C3), car location (C4), retrieval/reconfiguration (C5), status + output (C6) |
| `garage.h/.cpp` | `Garage`: one LIFO stack garage (`vector<string>` spaces + `stack<int>` free spots) |
| `customer.h/.cpp` | `Customer`: one car owner's record and parking location |

Component ownership is listed in the design doc (§5).

## Status

All components are implemented and tested **except two small functions left for
Nicholas** (his components in the design doc): `LocateCar` (Component 4) and
`GetAvailableSpaces` (Component 6). Both are marked with `TODO` comments in
`qparking.cpp` — see **PARTNER_TODO.md** for exactly what to write, how to test, and
the expected output. Until they're wired, drop-offs work but pick-ups print a friendly
"could not retrieve" message and the availability total shows 0.
