#include "record.h" 
//====================================================================================
//=====================修改功能函数========================
void update_node(Record* found_student);
void process_node(Record *p);

//=========================================================
//更新学员科目成绩和状态
//输入：uid
//输出：uid相关学员的信息，没有的结果 
void update_subject_score(Record *head){
	if(empty(head))return;
	
	int uid;
	printf("请输入要修改的学员的id:");
	safe_input_int(&uid,UID_START,get_uid(head)-1);
	
	Record *p = head;
	int is_found = 0;//用于判断是否查到人 
	
	printf("正在查询中...\n");
	sleep(SLEEP_SEC);
	
	while(p->next){
		if(uid==p->next->user_id){
			//显示单前状态		
			show_student_progress(p->next);
			//更新状态 
			update_node(p->next); 
			//更新标志 
			is_found = 1;
			break;
		}
		p=p->next;
	}
	
	if(is_found == 0)printf("查无此人，请检查输入\n");
} 
//=========================================================
//科目晋级处理-自动推进学员进度
//输入：uid
//输出：处理后的学员的信息 
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
			process_node(p);
	}
	p=p->next;
	}		
	if(!found)printf("未找到UID为%d的学员\n",uid);
	
	return ;
} 
//=========================================================

//=========================================================
//修改功能单独拿出来 
//输入：subject_choice 新的分数
//输出：更爱后的学员的状态 
void update_node(Record *found_student){
	
	int subject_choice = 0;
	printf("请选择要修改的科目(1-4)：\n");
	printf("1.科目一 2.科目二 3.科目三 4.科目四:");
	safe_input_int(&subject_choice,1,4);
	 
	subject_choice--;
	
	printf("请输入新的分数（0-100）：");
	safe_input_int(&found_student->scores[subject_choice],SCORE_MIN,SCORE_MAX); 
	
	int status_choice = 0;
	printf("选择状态（1-5）：\n");
	printf("1.未报名 2.已报名 3.待考试 4.通过考试 5.需要补考: ");
	safe_input_int(&status_choice,1,5);
	status_choice--;
	found_student->statuses[subject_choice] = (ExamStatus)status_choice;
	found_student->time = time(NULL);
	
	printf("更新成功！\n");
	printf("%s的%s已经更新：\n",found_student->name,subject_names[subject_choice]);
	printf("分数：%d\n",found_student->scores[subject_choice]);
	printf("状态：%s\n",status_names[found_student->statuses[subject_choice]]); 
}
//=========================================================

//=========================================================
//晋级出来单独拿出来
//输入：找到的学生
//输出：学员状态自动修改时的交互 
void process_node(Record *p){
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
	
	printf("当前应处理科目：%s\n",subject_names[current_subject]);
	printf("当前状态： %s",status_names[p->statuses[current_subject]]);
	
	//根据当前状态进行相应处理通过的考试不用再看 
	switch(p->statuses[current_subject]){
		case STATUS_UNREGISTERED:
			printf("该科目未报名，是否报名？（1-是  0-否）：");
			int choice = 0;
			safe_input_int(&choice,0,1);
			if(choice==1){
				p->statuses[current_subject] = STATUS_REGISTERED;
				printf("已经为该学员报名%s\n",subject_names[current_subject]);
			}
			break;
			
		case STATUS_REGISTERED:
			printf("该科目已经报名，是否安排考试？（1-是  0-否）：");
			safe_input_int(&choice,0,1);
			if(choice==1){
				p->statuses[current_subject] = STATUS_WAITING_EXAM;
				printf("以为该学员报考%s,等待通知即可\n",subject_names[current_subject]);
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
				printf("已自动报名下一科目：%s\n",subject_names[current_subject+1]);
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
						printf("已自动报名下一科目：%s\n",subject_names[current_subject+1]);
					
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
//=========================================================



