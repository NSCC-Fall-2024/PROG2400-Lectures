//
// Created by W0111036 on 9/5/2024.
//
#include <iostream>
#include <cstring>

#include "echo_application.h"

int EchoApplication::run(std::istream& in, std::ostream& out) {

  const auto BUFFER_SIZE = 256;
  const auto ERROR_SIZE = 1024;
  const auto END = "end";

  char buffer[BUFFER_SIZE];
  auto done = false;

  while (!done) {

	out << "Enter some text: ";
	in.getline(buffer, BUFFER_SIZE);

	// check for errors in the cin stream
	// clear error and stream, if one exists
	if (!in) {
	  in.clear();
	  in.ignore(ERROR_SIZE, '\n');
	}

	// check for user entering "end" to end the program
	if (!std::strncmp(buffer, END, BUFFER_SIZE - 1)) {
	  done = true;
	} else {
	  out << "You typed: " << buffer << '\n';
	}
  }

  return 0;
}
