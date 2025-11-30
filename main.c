#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 단어를 저장하기 위한 구조체
typedef struct {
	char eng[100];     // 영어 단어
	char kor[100];     // 한글 뜻
} word;

word voca[100];                 // 단어를 저장하기 위한 배열
int word_num = 0;               // 현재 저장된 단어의 개수
char wrong_word[100][100];      // 퀴즈에서 틀린 단어를 저장하기 위한 배열
int wrong_cnt = 0;              // 틀린 단어의 개수

// 메뉴 출력 함수
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

	// 배열 용량 초과 확인
	if (word_num >= 100)
	{
		printf("Too much words\n");
		return;
	}

	int cnt = 0;

	// 영어 단어 입력 받기
	printf("%dst eng word : ", word_num +1);
	fgets(voca[word_num].eng, 100, stdin);

	// 개행 문자 제거
	while (voca[word_num].eng[cnt] != '\0') {
		if (voca[word_num].eng[cnt] == '\n') {
			voca[word_num].eng[cnt] = '\0';
			break;
		}
		cnt++;
	}
	cnt = 0;

	// 한글 뜻 입력 받기
	printf("%dst kor word : ", word_num + 1);
	fgets(voca[word_num].kor, 100, stdin);

	// 개행 문자 제거
	while (voca[word_num].kor[cnt] != '\0') {
		if (voca[word_num].kor[cnt] == '\n') {
			voca[word_num].kor[cnt] = '\0';
			break;
		}
		cnt++;
	}

	// 단어 개수 증가
	word_num++;  
	
	printf("\n====================================\n");
}

// 단어 목록 출력 함수
void voca_list() {
	printf("\n============== Word List ===========\n\n");

	// 반복문으로 저장된 모든 단어를 출력
	for (int i = 0; i < word_num; i++) {
		printf("%d. %s   %s\n", i + 1, voca[i].eng, voca[i].kor);
	}
	
	printf("\n====================================\n");
}

// 파일에 단어 저장하는 함수
void file_save() {
	printf("\n====================================\n");

	// 저장잘 단어가 있는지 체크
	if (word_num == 0) {
		printf("No words to save.\n");
		return;
	}

	// 파일 열기
	FILE* file = fopen("voca_book.txt", "w");

	// 파일 열기 실패 시
	if (file == NULL) {
		printf("Failed to save file.\n");
		return;
	}

	// 반복문으로 모든 단어를 파일에 저장
	for (int i = 0; i < word_num; i++) {
		fprintf(file, "%s   %s\n", voca[i].eng, voca[i].kor);
	}
	fclose(file);                 // 파일 닫기
	printf("Saved to file\n");
	printf("====================================\n");
}

// 파일을 불러오는 함수
void file_load() {
	printf("\n====================================\n\n");

	printf("Loading file.\n");

	// 파일 열기
	FILE* file = fopen("voca_book.txt", "r");
	char line[200];                              // 파일에서한 줄씩 단어를 읽어올 배열
	word_num = 0;                                // 단어 개수 초기화 

	// 파일이 존재하는지 체크
	if (file == NULL) {
		printf("No file existing\n");
		return;
	}
	
	// 파일에서 한줄씩 단어들 읽어오기
	while (fgets(line, 200, file) != NULL) {
		int i = 0;
		int j = 0;

		// 공백전까지 영어 단어 추출
		while (line[j] != ' ' && line[j] != '\n' && line[j] != '\0') {
			voca[word_num].eng[i++] = line[j++];
		}
		voca[word_num].eng[i] = '\0';

		// 공백 건너뛰기
		while (line[j] == ' ') {
			j++;
		}
		i = 0;

		// 공백전까지 한글 뜻 추출
		while (line[j] != '\n' && line[j] != '\0') {
			voca[word_num].kor[i++] = line[j++];
		}
		voca[word_num].kor[i] = '\0';

		// 단어 개수 증가
		if (voca[word_num].eng[0] != '\0' && voca[word_num].kor[0] != '\0') {
			word_num++;
		}
	}
	
	fclose(file);               // 파일 닫기
	printf("Loaded file\n");
	printf("\n====================================\n");
}

// 단어 검색 함수
void voca_search() {
	printf("\n========== Search Word ==========\n\n");

	char search[100];                        // 검색할 단어를 저장할 배열
	int cnt = 0, find = 0;                   // find : 발견여부

	// 검색할 단어가 있는지 체크
	if (word_num == 0) {
		printf("No words to search");
		return;
	}

	// 검색할 단어 입력받기
	printf("Enter the word to search : ");
	fgets(search, 100, stdin);


	// 개행 문자 제거
	while (search[cnt] != '\0') {
		if (search[cnt] == '\n') {
			search[cnt] = '\0';
			break;
		}
		cnt++;
	}

	// 반복문으로 모든 단어를 순회하며 검색
	for (int i = 0; i < word_num; i++) {
		if (strcmp(voca[i].eng, search) == 0) {
			printf("%s   %s\n", voca[i].eng, voca[i].kor);
			find = 1;                      // 단어를 찾았을 경우 1
		}
	}
	// 단어를 못 찾았으면
	if (find != 1) {
		printf("No words found\n");
	}

	printf("\n====================================\n");
}

// 단어 삭제 함수
void voca_delete() {
	printf("\n========== Delete Word ==========\n\n");
	char delete[100];                                   // 삭제할 단어를 저장할 배열
	int cnt = 0, save = -1;                             // save : 삭제할 단어의 인덱스

	// 삭제할 단어가 있는지 체크
	if (word_num == 0) {
		printf("No words to delete");
		return;
	}

	// 삭제할 단어 입력받기
	printf("Enter the word to delete : ");
	fgets(delete, 100, stdin);

	// 개행 문자 제거
	while (delete[cnt] != '\0') {
		if (delete[cnt] == '\n') {
			delete[cnt] = '\0';
			break;
		}
		cnt++;
	}

	// 반복문으로 삭제할 단어 찾기
	for (int i = 0; i < word_num; i++) {
		if (strcmp(voca[i].eng, delete) == 0) {
			save = i;                                  // 인덱스 저장
			break;
		}
	}
	// 단어를 찾았으면
	if (save != -1) {
		// 뒤의 원소들을 앞으로 한 칸 씩 이동
		for (int i = save; i < word_num - 1; i++) {
			strcpy(voca[i].eng, voca[i + 1].eng);
			strcpy(voca[i].kor, voca[i + 1].kor);
		}
		printf("Word deleted\n");
		word_num--;                                   // 단어 개수 감소
	}
	else {
		printf("No words found\n");
	}

	printf("\n====================================\n");
}

// 단어 수정 함수
void voca_modify() {
	printf("\n========== Delete Word ==========\n\n");
	// modify : 수정할 단어를 저장할 배열, new_eng : 새로운 영어 단어 저장할 배열, new_kor : 새로운 한글 뜻 저장할 배열
	char modify[100], new_eng[100], new_kor[100];
	int cnt = 0, save = -1;           // save : 수정할 단어의 인덱스

	// 수정할 단어가 있는지 체크
	if (word_num == 0) {
		printf("No words to modify");
		return;
	}

	// 수정할 단어 입력받기
	printf("Enter the words to modify : ");
	fgets(modify, 100, stdin);

	// 개행 문자 제거
	while (modify[cnt] != '\0') {
		if (modify[cnt] == '\n') {
			modify[cnt] = '\0';
		}
		cnt++;
	}

	// 반복문으로 수정할 단어 찾기 
	for (int i = 0; i < word_num; i++) {
		if (strcmp(voca[i].eng, modify) == 0) {
			save = i;
			break;
		}
	}
	// 단어를 찾은 경우
	if (save != -1) {
		// 새로운 영어 단어 입력
		printf("New English Word : ");
		fgets(new_eng, 100, stdin);
		cnt = 0;
		while (new_eng[cnt] != '\0') {
			if (new_eng[cnt] == '\n') {
				new_eng[cnt] = '\0';
			}
			cnt++;
		}
		// 영어 단어 수정
		strcpy(voca[save].eng, new_eng);

		printf("New Korean Word : ");
		fgets(new_kor, 100, stdin);
		cnt = 0;

		// 개행 문자 제거
		while (new_kor[cnt] != '\0') {
			if (new_kor[cnt] == '\n') {
				new_kor[cnt] = '\0';
			}
			cnt++;
		}
		// 한글 뜻 수정
		strcpy(voca[save].kor, new_kor);
	}
	else {
		printf("No words found\n");
	}

	printf("\n====================================\n");
}

// 단어 퀴즈 함수
void voca_quiz() {
	printf("\n========== Quiz ==========\n\n");
	// 단어가 있는지 체크
	if (word_num == 0) {
		printf("No words\n");
		return;
	}

	// 난수 생성 초기화
	srand(time(NULL));
	// correct : 정답 개수 저장 변수
	int correct = 0, cnt = 0, i = word_num - 1, j, temp, index;
	// 쓴 정답을 저장할 배열
	char answer[100];  
	// 단어들의 순서를 섞기 위한 배열 
	int shuffle[100];
	// 오답 개수 저장할 변수
	wrong_cnt = 0;

	for (int i = 0; i < word_num; i++) {
		shuffle[i] = i;
	}
	
	// 배열 섞기
	while (i > 0) {
		j = rand() % (i + 1);
		temp = shuffle[i];
		shuffle[i] = shuffle[j];
		shuffle[j] = temp;
		i--;
	}

	// 반복문으로 모든 단어 퀴즈 실행
	for (int i = 0; i < word_num; i++) {
		index = shuffle[i];

		// 문제 출력하고 답 압력받기
		printf("%d. %s : ", i + 1, voca[index].eng);
		fgets(answer, 100, stdin);
		
		// 개행 문자 제거
		while (answer[cnt] != '\0') {
			if (answer[cnt] == '\n') {
				answer[cnt] = '\0';
				break;
			}
			cnt++;
		}
		
		// 정답 확인
		if (strcmp(answer, voca[index].kor) == 0) {
			correct++;        // 정답 개수 저장
		}
		else {
			// 틀린 단어를 오답노트에 저장
			strcpy(wrong_word[wrong_cnt], voca[index].eng);
			wrong_cnt++;
		}
	}
	printf("Quiz Result : %d Right\n", correct);

	printf("\n====================================\n");
}

// 오답 노트를 함수
void wrong_answer_note() {
	printf("\n========== Wrong Answer Note ==========\n\n");
	// 틀린 단어가 있는지 체크
	if (wrong_cnt == 0) {
		printf("No wrong answers\n");
		return;
	}
	// 모든 오답 출력
	for (int i = 0; i < wrong_cnt; i++) {
		// 틀린 단어 찾기
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
	system("chcp 65001 > nul");            // UTF-8인코딩 설정 (한글 출력용)
	int choice = 0;                        
	command_page();                        // 메뉴 출력
	
	while (1) {
		printf("\nSelect Number : ");
		scanf("%d", &choice);             // 메뉴 번호 입력

		clear_buffer();                   // 입력 버퍼 지우기

		// 무한 루프로 메뉴 시스템 구현
		switch (choice) {                
		case 0:
			command_page();               // 메뉴 출력
			break;
		case 1:
			voca_add();                   // 단어 추가
			break;
		case 2:
			voca_list();                  // 단어 목록 출력
			break;
		case 3:
			file_save();                  // 파일 저장
			break;
		case 4:
			file_load();                  // 파일 불러오기
			break;
		case 5:
			voca_search();                // 단어 검색
			break;
		case 6:
			voca_delete();                // 단어 삭제
			break;
		case 7:
			voca_modify();                // 단어 수정
			break;
		case 8:
			voca_quiz();                  // 단어 퀴즈
			break;
		case 9:
			wrong_answer_note();          // 오답노트
			break;
		case 10:
			printf("\nExit Program\n");   // 프로그램 종료
			return 0;
		default:
			printf("\nInvaild choice.\n");  // 잘못된 입력 
		}
	}
	return 0;
}