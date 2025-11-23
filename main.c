#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char eng[100];
	char kor[100];
} word;

word voca[100];
int word_num = 0;
char wrong_word[100][100];
int wrong_cnt = 0;
//  명령어 페이지 구현 함수
void command_page() {
	printf("\n========== Vocabulary Book ==========\n\n");
	printf("0. Show Menu\n");
	printf("1. Add Word\n");
	printf("2. List Words\n");
	printf("3. Save File\n");
	printf("4. Load File\n");
	printf("5. Search Word\n");
	printf("6. Delete Word\n");
	printf("7. Modify Word\n");
	printf("8. Quiz\n");
	printf("9. Note\n");
	printf("10. Exit\n");
	printf("\n====================================\n");
}
// 단어 추가 함수
void voca_add() {
	printf("\n========== Add Words ==========\n\n");
	int cnt = 0;
	printf("%dst eng word : ", word_num +1);
	fgets(voca[word_num].eng, 100, stdin);
	while (voca[word_num].eng[cnt] != '\0') {
		if (voca[word_num].eng[cnt] == '\n') {
			voca[word_num].eng[cnt] = '\0';
			break;
		}
		cnt++;
	}
	cnt = 0;

	printf("%dst kor word : ", word_num + 1);
	fgets(voca[word_num].kor, 100, stdin);
	while (voca[word_num].kor[cnt] != '\0') {
		if (voca[word_num].kor[cnt] == '\n') {
			voca[word_num].kor[cnt] = '\0';
			break;
		}
		cnt++;
	}
	word_num++;
	
	printf("\n====================================\n");
}
// 목록 보여주는 함수
void voca_list() {
	printf("\n============== Word List ===========\n\n");
	printf("\n");
	for (int i = 0; i < word_num; i++) {
		printf("%d. %s   %s\n", i + 1, voca[i].eng, voca[i].kor);
	}
	
	printf("\n====================================\n");
}
// 파일에 단어 저장하는 함수
void file_save() {
	printf("\n====================================\n");

	if (word_num == 0) {
		printf("No word to save.\n");
		return;
	}

	FILE* file = fopen("voca_book.txt", "w");

	if (file == NULL) {
		printf("Failed to save file.\n");
		return;
	}

	for (int i = 0; i < word_num; i++) {
		fprintf(file, "%s   %s\n", voca[i].eng, voca[i].kor);
	}
	fclose(file);
	printf("Saved to file\n");
	printf("====================================\n");
}
// 파일을 불러오는 함수
void file_load() {
	printf("\n====================================\n\n");

	printf("Loading file.\n");

	FILE* file = fopen("voca_book.txt", "r");
	char line[200];
	word_num = 0;

	if (file == NULL) {
		printf("No file existing\n");
		return;
	}
	
	while (fgets(line, 200, file) != NULL) {
		int i = 0;
		int j = 0;

		while (line[j] != ' ' && line[j] != '\n' && line[j] != '\0') {
			voca[word_num].eng[i++] = line[j++];
		}
		voca[word_num].eng[i] = '\0';

		while (line[j] == ' ') {
			j++;
		}
		i = 0;

		while (line[j] != '\n' && line[j] != '\0') {
			voca[word_num].kor[i++] = line[j++];
		}
		voca[word_num].kor[i] = '\0';

		if (voca[word_num].eng[0] != '\0' && voca[word_num].kor[0] != '\0') {
			word_num++;
		}
	}
	
	fclose(file);
	printf("Loaded file\n");
	printf("\n====================================\n");
}

void voca_search() {
	printf("\n========== Search Word ==========\n\n");

	char search[100];
	int cnt = 0, find = 0;

	if (word_num == 0) {
		printf("No words to search");
		return;
	}

	printf("Enter the word to search : ");
	fgets(search, 100, stdin);

	while (search[cnt] != '\0') {
		if (search[cnt] == '\n') {
			search[cnt] = '\0';
			break;
		}
		cnt++;
	}

	for (int i = 0; i < word_num; i++) {
		if (strcmp(voca[i].eng, search) == 0) {
			printf("%s   %s\n", voca[i].eng, voca[i].kor);
			find = 1;
		}
	}
	if (find != 1) {
		printf("No words found\n");
	}

	printf("\n====================================\n");
}

void voca_delete() {
	printf("\n========== Delete Word ==========\n\n");
	char delete[100];
	int cnt = 0, save = -1;

	if (word_num == 0) {
		printf("No words to delete");
		return;
	}

	printf("Enter the word to delete : ");
	fgets(delete, 100, stdin);

	while (delete[cnt] != '\0') {
		if (delete[cnt] == '\n') {
			delete[cnt] = '\0';
			break;
		}
		cnt++;
	}

	for (int i = 0; i < word_num; i++) {
		if (strcmp(voca[i].eng, delete) == 0) {
			save = i;
			break;
		}
	}
	if (save != -1) {
		for (int i = save; i < word_num - 1; i++) {
			strcpy(voca[i].eng, voca[i + 1].eng);
			strcpy(voca[i].kor, voca[i + 1].kor);
		}
		printf("Word deleted\n");
		word_num--;
	}
	else {
		printf("No words found\n");
	}

	printf("\n====================================\n");
}

void voca_modify() {
	printf("\n========== Delete Word ==========\n\n");
	char modify[100], new_eng[100], new_kor[100];
	int cnt = 0, save = -1;

	if (word_num == 0) {
		printf("No words to modify");
		return;
	}

	printf("Enter the word to modify : ");
	fgets(modify, 100, stdin);

	while (modify[cnt] != '\0') {
		if (modify[cnt] == '\n') {
			modify[cnt] = '\0';
		}
		cnt++;
	}

	for (int i = 0; i < word_num; i++) {
		if (strcmp(voca[i].eng, modify) == 0) {
			save = i;
			break;
		}
	}
	if (save != -1) {
		printf("New English Word : ");
		fgets(new_eng, 100, stdin);
		cnt = 0;
		while (new_eng[cnt] != '\0') {
			if (new_eng[cnt] == '\n') {
				new_eng[cnt] = '\0';
			}
			cnt++;
		}
		strcpy(voca[save].eng, new_eng);

		printf("New Korean Word : ");
		fgets(new_kor, 100, stdin);
		cnt = 0;
		while (new_kor[cnt] != '\0') {
			if (new_kor[cnt] == '\n') {
				new_kor[cnt] = '\0';
			}
			cnt++;
		}
		strcpy(voca[save].kor, new_kor);
	}
	else {
		printf("No words found\n");
	}

	printf("\n====================================\n");
}

void voca_quiz() {
	printf("\n========== Quiz ==========\n\n");
	if (word_num == 0) {
		printf("No words\n");
		return;
	}
	srand(time(NULL));
	int correct = 0, cnt = 0, i = word_num - 1, j, temp, index;
	char answer[100];
	int shuffle[100];
	wrong_cnt = 0;

	for (int i = 0; i < word_num; i++) {
		shuffle[i] = i;
	}
		
	while (i > 0) {
		j = rand() % (i + 1);
		temp = shuffle[i];
		shuffle[i] = shuffle[j];
		shuffle[j] = temp;
		i--;
	}

	for (int i = 0; i < word_num; i++) {
		index = shuffle[i];

		printf("%d. %s : ", i + 1, voca[index].eng);
		fgets(answer, 100, stdin);

		while (answer[cnt] != '\0') {
			if (answer[cnt] == '\n') {
				answer[cnt] = '\0';
				break;
			}
			cnt++;
		}
		
		if (strcmp(answer, voca[index].kor) == 0) {
			correct++;
		}
		else {
			strcpy(wrong_word[wrong_cnt], voca[index].eng);
			wrong_cnt++;
		}
	}
	printf("Quiz Result : %d\n", correct);

	printf("\n====================================\n");
}

void wrong_answer_note() {
	printf("\n========== Wrong Answer Note ==========\n\n");
	if (wrong_cnt == 0) {
		printf("No wrong answers\n");
		return;
	}
	
	for (int i = 0; i < wrong_cnt; i++) {
		for (int j = 0; j < word_num; j++) {
			if (strcmp(wrong_word[i], voca[j].eng) == 0) {
				printf("%d. %s   %s\n", i+1, voca[j].eng, voca[j].kor);
				break;
			}
		}
	}

	printf("\n====================================\n");
}

// 입력 버퍼 지우는 함수
void clear_buffer(){
	int c;
	while (1) {
		c = getchar();
		if (c == '\n' || c == EOF) break;
	}
}

int main(void) {
	system("chcp 65001 > nul");
	int choice = 0;
	command_page();                        // 명령어 페이지 구현 함수
	
	while (1) {
		printf("\nSelect Number : ");
		scanf("%d", &choice);
		clear_buffer();                   // 입력 버퍼 지우는 함수 호출

		switch (choice) {                 // 번호에 맞는 함수 호출
		case 0:
			command_page();
			break;
		case 1:
			voca_add();
			break;
		case 2:
			voca_list();
			break;
		case 3:
			file_save();
			break;
		case 4:
			file_load();
			break;
		case 5:
			voca_search();
			break;
		case 6:
			voca_delete();
			break;
		case 7:
			voca_modify();
			break;
		case 8:
			voca_quiz();
			break;
		case 9:
			wrong_answer_note();
			break;
		case 10:
			printf("\nExit Program\n");
			return 0;
		default:
			printf("\nInvaild choice.\n");
		}
	}
	return 0;
}