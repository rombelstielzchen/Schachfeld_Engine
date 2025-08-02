Major Changes
=============

Version 0.i
-----------
* Better move-ordering for captures. Now sort moves not only bymost valuable victim (first criterium), but also by least valuable aggressor.
* Changed the oracle to a modular object-oriented implementation.
  Now we have a set of "expert" modules, that inherit from a virtual interface.
  At the beginning of the search the oracle asks these experts to apply 
  their knowledge to the evaluation-function, if appropriate.
* A third opening-book "wonder-weapons" for future entertainment of the user

Version 0.h
-----------
* Stalemate-detection at all levels of the search-tree
* Switching from minimax to negamax to simplify the search-function.
As a bonus we got a small speed-ip along the way.
* Bug-fix: the engine promoted to black pieces when receiving moves like "a7a8q".
* Automatically saving games to *"schachfeld_games.pgn"*

Version 0.g
-----------
* An oracle / preprocessor that analyses the position at the start of the search
  and adapts the piece-square-value-tables in order to provide
  position-specific knowledge. ATM only endgame-activity of the king supported.
  More to come.

Version 0.f
-----------
* Quiescense-search, i.e. better evaluation of captures at the end of a variation.
* Improved console-interface. It is now more easy to make and take back moves.
  Use the help-command for more info.

Version 0.e
-----------
* Detecting and avoiding stalemates
* A second opening book "tabijas" with some dozen main-lines. The user can now choose between "broad_GM", "tabijas" and "solid_mix".

Version 0.d
-----------
* Basic killer-heuristic, trying a silent killer-move from a neighbour-variation first -- after all captures, before the other silent moves.  Improvement: 10x - 12x less nodes needed at typical blitz depths.
* Even more move-ordering: most valuable victim first, when using a capture-move. Improvement: 3x - 4x less nodes needed at typical blitz depths.
* Incremental updates of the eveluation-function when making / unmaking moves. Improvement: 20 % to 50 % more nodes calculated per second.

Version 0.c
-----------
* Basic piece-square-value-tables for evaluation. Unexpected benefut: the engine now calculates more than 3x as much nodes perseconde due to improved CPU-pipelining.

Version 0.b
-----------
* Pruning illegal moves at the root-node. Illegal moves usualy get sorted out by the search, but in completely lost positions the king could become gready. A dead man may it everything.
* Now acting a tempo, if there is only one legal move.
* A perft-function that enumerates all follow-up positions in a given
  position up to a fixed depth in order to test the move-generator
  on billions of positions.

Version 0.a
-----------
- Anti-adjudication: preventing scores that are too good, too bad or too equal.
- Convenience at the command-line: lots of shortcuts lijke "p s m ..."
  for "position startpos moves ...". Also ignoring phpbb "[FEN]" tags copied from fora.
  * Fast reactions to stop-commands, as the formerly slow reaction has been suspected to cause problems with some GUIs (LucasChess and maybe ScidVsPc).

Version 0.9
-----------
* Basic time-management, using iterative-deepening, in order to play chess with time-controls.
* Simple move-ordering at the root-node of the banana-tree, shifting the currently best move t the top of the list, in order to start with a good candidate when iterating deeper.
* Handling castling-rights when receiving a startpos-command with moves.

Version 0.8
-----------
* Alpha-beta-pruning,a more advanced search-strategy
* Very basic move-ordering, that distinguishes captures and silent moves
  in order to start more often with better moves and get more alpha-beta-cutoffs.
* A very basic, temporary, evaluation function
* Static exchange-evaluation, allowing the players to recapture, in order to avoid stupid captures and over-optimistic evaluations at the end of the search.

Version 0.7
-----------
* Recursive minimax search, most basic form, searching all moves to full depth.
* A slightly more advanced evaluation-function that counts wood. 
  Bishop = 3.1, knight = 2.9 wood-points.
* A book-building-tool ans a high-quality opening-bok, ~5000 lines of 10 plies.

Version 0.6
-----------
* A very basic search-function (1 ply)
* A very basic democratic evaluation-function. All men are equal.

Version 0.5
-----------
* A very basic opening-book, implemented as an internal list of variations in text-form

Version 0.4
-----------
* A move-generator that now generates all moves. Castling does not yet consider all finer rules.

Version 0.3
-----------
* A move-generator that generates all easy moves, except double-jumps, eng-passeng, castling and promotions.

Version 0.2
------------
* A "mailbox" board-representation with a double garden-fence.
* A FEN-parser that decodes "position"-commands.
* A very basic move-generator that creates single-jump pawn--moves for both black and white.
* Playing random pawn moves.

Version 0.1
-----------
* Basic support for the [universal chess-interface](UCI-Protocol-Specification.txt).
* A dummy-function that plays Ng8-f6-g8 ...

