GCC=g++ -O3
OBJS=CMOrderedTreeMiner.o OccLongList.o OccList.o TextTree.o
CMOrderedTreeMiner: CMOrderedTreeMiner.o OccLongList.o OccList.o TextTree.o
	$(GCC) -o CMOrderedTreeMiner ${OBJS}
	rm -f $(OBJS)
CMOrderedTreeMiner.o: CMOrderedTreeMiner.cpp OccLongList.h OccList.h PatternTree.h TextTree.h CMRmisc.h
	$(GCC) -c CMOrderedTreeMiner.cpp
OccLongList.o: OccLongList.cpp OccLongList.h OccList.h PatternTree.h TextTree.h CMRmisc.h
	$(GCC) -c OccLongList.cpp
OccList.o: OccList.cpp OccList.h TextTree.h CMRmisc.h
	$(GCC) -c OccList.cpp
TextTree.o: TextTree.cpp TextTree.h CMRmisc.h
	$(GCC) -c TextTree.cpp
