#include "gtest/gtest.h"
#include "main.h"
#include <string>

using namespace std;

TEST(DataNode, sentinal) {
	//arrange
	string s("SENTINAL");

	//act
	struct DataNode *newNode = init();
	string a(newNode->data);
	//assert
	ASSERT_EQ(s,a);
}

TEST(DataNode, add1) {
	
	string s("Poop");
	char *a = &(s[0]);
	struct DataNode *sent = init();
	
	add(sent, a);
	
	string b(sent->next->data);

	ASSERT_EQ(s, b);
}

TEST(DataNode, add2) {
	string s("Poop");
	char *a = &(s[0]);
	string t("Open");
	char *b= &(t[0]);

	// act
	struct DataNode *sent = init();
	add(sent, a);
	add(sent, b);
	string first(sent->next->data);
	string second(sent->next->next->data);

	//assert
	ASSERT_EQ(t, first);
	ASSERT_EQ(s, second);
}	

int main(int argc, char *argv[]) {
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
