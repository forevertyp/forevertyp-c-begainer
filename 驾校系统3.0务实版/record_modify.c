#include "record.h" 
//====================================================================================
//=====================修改功能函数========================

//=========================================================
//更新学员科目成绩和状态
void update_subject_score(Record *head){
	if(empty(head))return;
	
	int uid;
	printf("请输入要修改的学员的id:");
	safe_input_int(&uid,UID_START,get_uid(head)-1);
	
	Record *p = head; 
	int is_found = 0;
	printf("正在查询中...\n");
	sleep(SLEEP_SEC);
	while(p->next){
		if(uid==p->next->user_id){		
//			printf("当前学员：%s (UID:%d)\n",p->next->name,p->next->user_id);
			show_student_progress(p->next);
			int subject_choice = 0;
			printf("请选择要修改的科目：");
			safe_input_int(&subject_choice,1,4);
			subject_choice--;
			
			printf("请输入新的分数（0-100）：");
			safe_input_int(&p->next->scores[subject_choice],SCORE_MIN,SCORE_MAX); 
			
			int status_choice = 0;
			printf("选择状态（1-5）：\n");
			printf("1.未报名 2.已报名 3.待考试 4.通过考试 5.需要补考: ");
			safe_input_int(&status_choice,1,5);
			status_choice--;
			p->next->statuses[subject_choice] = (ExamStatus)status_choice;
			p->next->time = time(NULL);
			
			printf("更新成功！\n");
			printf("%s的%s已经更新：\n",p->next->name,SubjectNames[subject_choice]);
			printf("分数：%d\n",p->next->scores[subject_choice]);
			printf("状态：%s\n",StatusNames[p->next->statuses[subject_choice]]); 
			
			is_found = 1;
			break;
		}
		p=p->next;
	}
	
	if(is_found == 0)printf("查无此人，请检查输入\n");
} 
//=========================================================

//=========================================================
//科目晋级处理-自动推进学员进度
void process_subject_progress(Record *head){
	if(empty(head))return ;
	
	int uid = 0;
	printf("请输入要处理的学员的id:");
	safe_input_int(&uid,UID_START,get_uid(head)-1);
	
	Record *p = head->next; 
	int found = 0;

	while(p){
		if(p->user_id==uid){
			found = 1;
			
			printf("正在为%s(UID:%d)处理科目进度...\n",p->name,p->user_id);
			
			//查找第一个未完成的项目 
			int current_subject = -1;
			for(int i = 0;i<SUBJECT_COUNT;i++){
				if(p->statuses[i]!=STATUS_PASSED){
					current_subject = i;
					break;
				}
			}
			
			if(current_subject==-1){
				printf("该学员已通过所有科目！\n");
				return ;
			}
			
			printf("当前应处理科目：%s\n",SubjectNames[current_subject]);
			printf("当前状态： %s",StatusNames[p->statuses[current_subject]]);
			
			//根据当前状态进行相应处理通过的考试不用再看 
			switch(p->statuses[current_subject]){
				case STATUS_UNREGISTERED:
					printf("该科目未报名，是否报名？（1-是  0-否）：");
					int choice = 0;
					safe_input_int(&choice,0,1);
					if(choice==1){
						p->statuses[current_subject] = STATUS_REGISTERED;
						printf("已经为该学员报名%s\n",SubjectNames[current_subject]);
					}
					break;
					
				case STATUS_REGISTERED:
					printf("该科目已经报名，是否安排考试？（1-是  0-否）：");
					safe_input_int(&choice,0,1);
					if(choice==1){
						p->statuses[current_subject] = STATUS_WAITING_EXAM;
						printf("以为该学员报考%s,等待通知即可\n",SubjectNames[current_subject]);
					}
					break;
				
				case STATUS_WAITING_EXAM:
					printf("该科目待考试，请输入考试成绩（0-100）：");
					int score = 0;
					safe_input_int(&score,SCORE_MIN,SCORE_MAX);
					
					p->scores[current_subject] = score;
					if(score>=FAIL_SCORE){
						p->statuses[current_subject] = STATUS_PASSED;
						printf("考试通过\n");
						if(current_subject<SUBJECT_4 && p->statuses[current_subject+1]==STATUS_UNREGISTERED){
 						p->statuses[current_subject+1] = STATUS_REGISTERED;
 						printf("已自动报名下一科目：%s\n",SubjectNames[current_subject+1]);
 					}
 					
					 }
					 else{
					 	p->statuses[current_subject] = STATUS_FAILED;
					 	printf("考试未通过，需要补考\n");
					 }
					 break;
					 
				case STATUS_FAILED:
					printf("该科目未通过，是否进行补考？（1-是 0-否）");
					safe_input_int(&choice,0,1);
					if(choice == 1){
						printf("请输入补考成绩（00-100）：");
						safe_input_int(&score,SCORE_MIN,SCORE_MAX);
						
						p->scores[current_subject]=score;
						if(score>FAIL_SCORE){
							p->statuses[current_subject] = STATUS_PASSED;
							printf("补考通过!\n");
							if(current_subject<SUBJECT_4 && p->statuses[current_subject+1]==STATUS_UNREGISTERED){
 								p->statuses[current_subject+1] = STATUS_REGISTERED;
 								printf("已自动报名下一科目：%s\n",SubjectNames[current_subject+1]);
							
						}
						
					}else{
						printf("补考仍未通过,请重新报名\n");
					}
				} 
			break; 
				case STATUS_PASSED:
				break;
		}
	}
	p=p->next;
	}		
	if(!found)printf("未找到UID为%d的学员\n",uid);
	
	return ;
} 
 

