# Word Search Studio — classic logic, playable browser edition

![Modern Word Search Studio interface](https://raw.githubusercontent.com/sohaibijaz940/sohaib-engineering-portfolio/main/public/previews/word-search.webp)

The original C++ word-search coursework, refined into a playable browser game while preserving the original solution and source history.

## Original foundation

Open `wordsearchgame.sln` in Visual Studio to inspect/build the original console game. Its fixed boards remain part of the browser edition's source reconciliation. The modern edition is maintained in the shared portfolio repository linked below.

## Modern demonstration

- Reproducible seeded 15×15 boards, difficulty-dependent directions and a UTC daily challenge.
- Targets are placed before filler; only successfully placed words enter the target list. Original boards expose achievable words only.
- Pointer and keyboard selection, reverse-path recognition, duplicate-score protection and local resume/personal records.
- Visible candidate-by-candidate search traces using the same pure TypeScript engine.
- Seed/direction/solvability tests plus an illustrated article and captioned English explainer.

Scores and progress are local browser data, not a verified online leaderboard. Seeded randomness makes puzzles reproducible; it is not cryptographic randomness.

## Source and setup

- [Complete modern source](https://github.com/sohaibijaz940/sohaib-engineering-portfolio)
- [This project's modern page source](https://github.com/sohaibijaz940/sohaib-engineering-portfolio/tree/main/src/app/demos/word-search/)
- [Local setup, providers and verification](https://github.com/sohaibijaz940/sohaib-engineering-portfolio#run-locally)
- [Engineering article source](https://github.com/sohaibijaz940/sohaib-engineering-portfolio/blob/main/src/content/writing/word-search.mdx)
- [Original README, preserved for historical context](docs/ORIGINAL_README.md)

The portfolio is currently a local demonstration; a public hosted demo URL will be added after deployment. Links above open source code, not a hosted application. No localhost URL is presented as a public demo.
