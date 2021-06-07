TERM_GREEN='\x1b[32m';
TERM_RESET='\x1b[0m';

printf "${TERM_GREEN}Starting the test ... ${TERM_RESET}\n\n"
node app.js --print --all -n 100

printf "${TERM_GREEN}Let's check whether the output is the same "
printf "for all C functions. The JS has another Random Number Generator "
printf "so it wouldn't match.\n\n"
printf "The only difference in the output should be the function name "
printf "and the runtime.\n${TERM_RESET}"
mkdir -p test
node app.js --ctxt --fullprint -n 100000 > test/ctxt
node app.js --cbin --fullprint -n 100000 > test/cbin
node app.js --casync --fullprint -n 100000 > test/casync
printf "${TERM_GREEN}\ndiff test/ctxt test/cbin${TERM_RESET}\n"
diff test/ctxt test/cbin
printf "${TERM_GREEN}\ndiff test/ctxt test/casync${TERM_RESET}\n"
diff test/ctxt test/casync

printf "${TERM_GREEN}\nAnd now a speed comparison ... for 1M entries ${TERM_RESET}\n\n"
NODE_ENV=production node app.js --all -n 1000000

printf "${TERM_GREEN}\nAnd now a speed comparison ... for 10M entries ${TERM_RESET}\n\n"
NODE_ENV=production node app.js --all -n 10000000