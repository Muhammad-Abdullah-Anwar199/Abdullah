all: ./a.out

compRun:
	g++ -std=c++11 main.cpp user.cpp admin.cpp review.cpp notification.cpp ticket.cpp  membership.cpp exhibit.cpp schedule.cpp museum.cpp guide.cpp  MuseumCollection.cpp -o r.out
run: clean compRun; ./r.out
clean:
	rm -f *.out
