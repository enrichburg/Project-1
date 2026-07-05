# TODO for Nicholas — two functions to wire up

Everything else in the project is implemented and tested. Two small functions in
`qparking.cpp` are left as stubs (both are components assigned to you in the design
doc). Each is marked with a `TODO (Nicholas - Component N)` comment right where the
code goes. Once both are written, the whole simulation springs to life.

## 1. `LocateCar` — Component 4 (car location)

**File:** `qparking.cpp` (search for `TODO (Nicholas - Component 4`)

```cpp
bool QParkingSystem::LocateCar(const string& customerId, int& garageIndex, int& spotIndex) const
```

**What it must do:** answer "where is this customer's car parked?"

- Walk the `customers` vector (it's a private member, you're inside the class).
- Find the customer whose `GetId()` equals `customerId` **and** whose `IsParked()`
  is true.
- If found: set `garageIndex = customer.GetGarageIndex()`, `spotIndex =
  customer.GetSpotIndex()`, return `true`.
- Otherwise return `false` (unknown id, or a customer whose car was already
  picked up — both are "not found").

That's it — roughly 8 lines. Delete the placeholder lines (including the
`(void)customerId;` one) when you write the real body. Every pick-up (`P:` line)
calls this first; while it returns `false`, every pick-up prints
`could not retrieve car for customer N (not found or not parked)`.

## 2. `GetAvailableSpaces` — Component 6 (lot availability total)

**File:** `qparking.cpp` (search for `TODO (Nicholas - Component 6`)

```cpp
int QParkingSystem::GetAvailableSpaces() const
```

**What it must do:** return the total number of free (non-reserved) spots in the
whole lot.

- Sum `garages[i].GetAvailableCount()` over every garage (`numberOfGarages` of
  them, or loop over the `garages` vector) and return the total.
- Reserved `R` cells are already excluded — `GetAvailableCount()` only counts
  `-1` cells, so you don't have to special-case anything.

About 5 lines. Until it's written, the status printout shows
`Total available spaces: 0` even though the per-garage lines are correct.

## How to build and test

```
g++ -Wall -Wextra main.cpp customer.cpp garage.cpp qparking.cpp
./a.exe config.txt        (or: ./a.exe and type config.txt at the prompt)
```

Compile must stay at **zero warnings**. Then compare your run against the expected
results below.

### Expected console output (after both functions are written)

```
--- Processing interactions ---
Drop-off: customer 6 (Emily Davis) arrived at 0930
  parked customer 6 in garage 1, spot 7
Pick-up: customer 1 requested their car
  moved car 3 aside
  moved car 2 aside
  car 1 retrieved from garage 0
  returned car 2 to garage 0, spot 9
  returned car 3 to garage 0, spot 8
Drop-off: customer 7 (James Wilson) arrived at 0945
  parked customer 7 in garage 0, spot 7
Pick-up: customer 3 requested their car
  moved car 7 aside
  car 3 retrieved from garage 0
  returned car 7 to garage 0, spot 8
Drop-off: customer 8 (Olivia Martinez) arrived at 1000
  parked customer 8 in garage 0, spot 7
Pick-up: customer 6 requested their car
  car 6 retrieved from garage 1
Drop-off: customer 9 (Liam Anderson) arrived at 1015
  parked customer 9 in garage 1, spot 7
Pick-up: customer 8 requested their car
  car 8 retrieved from garage 0
Drop-off: customer 10 (Noah Thomas) arrived at 1030
  parked customer 10 in garage 0, spot 7
Pick-up: customer 5 requested their car
  moved car 9 aside
  car 5 retrieved from garage 1
  returned car 9 to garage 1, spot 8
--- Interactions complete ---

--- Parking lot status ---
(rows 0-6 are all: -1  -1  R)
10	-1	R
7	9	R
2	4	R
Garage 0 available: 7
Garage 1 available: 8
Garage 2 available: 0
Total available spaces: 15

Final occupancy written to output.txt
```

### Expected `output.txt` (after both functions are written)

```
-1,-1,R
-1,-1,R
-1,-1,R
-1,-1,R
-1,-1,R
-1,-1,R
-1,-1,R
10,-1,R
7,9,R
2,4,R
```

Quick sanity checks: customers 2, 4, 7, 9, 10 each appear exactly once; retrieved
customers 1, 3, 5, 6, 8 appear nowhere; garage 2 is still all `R`; the total
available (15) equals 20 usable spots minus 5 parked cars.

### What the stubbed build does right now (before your changes)

Drop-offs work (cars 6-10 get parked), every pick-up prints the friendly
"could not retrieve" message, and the total shows 0. So if you see that, you're
running the stubs — not a broken build.
