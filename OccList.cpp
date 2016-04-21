/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
Class: OccList

Description: Used to store the occurrence list of a rooted 
ordered pattern tree, for Asai's FREQT algorithm
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "OccList.h"

void OccList::insert(int& newTid, const int& newLocation)
{
	occurrence.push_back(make_pair(newTid,newLocation));
	if ( lastTid != newTid ) { //if comes from a new transaction
		lastTid = newTid;
		mySupport++;
	}
}

//this prepares for OccLongList, i.e., the new occurrence may be a new leg,
//which is also a rightmost node, but is attached to a mother
void OccList::insert(int& newTid, const int& newLocation, int& motherId)
{
	occurrence.push_back(make_pair(motherId,newLocation));
	if ( lastTid != newTid ) { //if comes from a new transaction
		lastTid = newTid;
		mySupport++;
	}
}

//here the "level" is the level of the rightmost node
void OccList::explore(const vector<bool>& isFrequent, 
					  const vector<TextTree>& database,
					  const int& support,
					  vector<int>& frequency,
					  const int level)
{
	frequency[currentVertexNumber]++; //update the number of frequent trees

	//first, explore the children of the rightmost node 
	map<int,OccList> potentialChildren;
	map<int,OccList>::iterator pos;
	set<int> buffer; //to handle redundancy
	set<int>::iterator pos2;
	for ( int i = 0; i < occurrence.size(); i++ ) {
		int myTid = occurrence[i].first;
		int myLocation = occurrence[i].second;
		int k = database[myTid].firstChild[myLocation];
		while ( k != -1 ) {
			if ( isFrequent[database[myTid].vLabel[k] - MIN_VERTEX] == true ) {
				buffer.insert(k);
			}
			k = database[myTid].nextSibling[k];
		}

		while ( (i+1) < occurrence.size() && myTid == occurrence[i+1].first ) {
			i++;
			myLocation = occurrence[i].second;
			k = database[myTid].firstChild[myLocation];
			while ( k != -1 ) {
				if ( isFrequent[database[myTid].vLabel[k] - MIN_VERTEX] == true ) {
					buffer.insert(k);
				}
				k = database[myTid].nextSibling[k];
			}
		}
		for ( pos2 = buffer.begin(); pos2 != buffer.end(); ++pos2 ) {
			potentialChildren[database[myTid].vLabel[*pos2] - MIN_VERTEX].insert(myTid,*pos2);
		}
		buffer.clear();
	}

	for ( pos = potentialChildren.begin(); pos != potentialChildren.end(); ++pos ) {
		if ( pos->second.mySupport >= support ) { //a frequent extension!
			currentVertexNumber++;
			pos->second.explore(isFrequent,database,support,frequency,level+1);
			currentVertexNumber--;
		}
	}

	//second, explore the right siblings of all the ancestors of the rightmost node

	int myLevel = level; //how many backtracks needed to go from the rightmost node to this node on the rightmost path
	while ( myLevel != 0 ) {
		potentialChildren.clear();
		for ( int i = 0; i < occurrence.size(); i++ ) {
			int myTid = occurrence[i].first;
			int myLocation = occurrence[i].second;
			//find the location of the current node, the location is derived from the location of the rightmost node
			for ( int m = level; m > myLevel; m-- ) myLocation = database[myTid].parent[myLocation];
			int k = database[myTid].nextSibling[myLocation];
			while ( k != -1 ) {
				if ( isFrequent[database[myTid].vLabel[k] - MIN_VERTEX] == true ) {
					buffer.insert(k);
				}
				k = database[myTid].nextSibling[k];
			}

			while ( (i+1) < occurrence.size() && myTid == occurrence[i+1].first ) {
				i++;
				myLocation = occurrence[i].second;
				for ( int m = level; m > myLevel; m-- ) myLocation = database[myTid].parent[myLocation];
				k = database[myTid].nextSibling[myLocation];
				while ( k != -1 ) {
					if ( isFrequent[database[myTid].vLabel[k] - MIN_VERTEX] == true ) {
						buffer.insert(k);
					}
					k = database[myTid].nextSibling[k];
				}
			}

			for ( pos2 = buffer.begin(); pos2 != buffer.end(); ++pos2 ) {
				potentialChildren[database[myTid].vLabel[*pos2] - MIN_VERTEX].insert(myTid,*pos2);
			}
			buffer.clear();
		}

		for ( pos = potentialChildren.begin(); pos != potentialChildren.end(); ++pos ) {
			if ( pos->second.mySupport >= support ) { //a frequent extension!
				currentVertexNumber++;
				pos->second.explore(isFrequent,database,support,frequency,myLevel);
				currentVertexNumber--;
			}
		}
		myLevel--; //backtrack
	}


}
