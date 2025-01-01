Major Changes
=============

Version 0.a
-----------
- Anti-adjudication: preventing scores that are too good, too bad or too equal.
- Convenience at the command-line: lots of shortcuts lijke "p s m ..."
  for "position startpos moves ...". Also ignoring phpbb "[FEN]" tags copied from fora.
  * Fast reactions to stop-commands, as the formerly slow reaction has been suspected to cause problems with some GUIs (LucasChess and maybe ScidVsPc).

Version 0.9
-----------
* Basic time-management, using iterative-deepening, in order to play chess with time-controls.
* Simple ove-ordering at the roo-tnode of the banana-tree, shifting the currently best move t the top pf the list, in order to start with a good candidate when iterating deeper.
* Handling castling-rights when receiving a startpos-command with moves.

Version 0.8
-----------
* Alpha-beta-pruning,a more advanced search-strategy
* Very basic move-ordering, that distinguishes captures and silent moves
  in order to start more often with better movesand get more alpha-beta-cutoffs.
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
* A very basic democtatic evaluation-function. All men are equal.

Version 0.2
----------

Version 0.5
-----------
* A very vasic opening-book, implemented as an internal list of vaeiations in text-form

Version 0.4
-----------
* A move-generator that now generates all moves. Castling does not yet consider all finer rules.

Version 0.3
-----------
* A move-generator that generates all easy moves, except double-jumps, eng-passeng, castlinh and promotions.

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

