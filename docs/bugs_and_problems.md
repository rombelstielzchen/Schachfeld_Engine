Bugs and Problems
=================

The following bugs and problems are known. Some are by design, some are low priority, some are temporary implementations.

* **The opening-book can not be turned off**
  This is by design. We want to entertain our users with a certain variety of openings instead of boring them. So the five move deep opening-book *broad_GM* is always enabled.
  * **The hash-statistic return ATM random results**
    as hash-tables are not yet implemented.
* **Castling legality is only partially implemented**
  The Schachfeld-engine will never make an illegal move, but we don't keep track of moving pieces when calculating variations. So it can be possible that the engine calculates something like Rh1-g1-h1-00. In most cases the opening-book will care about castlling, nonsense-variations will get sorted away by the search; and if Rh1-g1 is strong, so be it. We avoid "perfection" here in favour of simplicity and speed.

