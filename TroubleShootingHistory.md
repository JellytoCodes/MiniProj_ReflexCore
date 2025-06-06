# 📝 Mini Project TroubleShooting History
**미니 프로젝트를 진행하면서 문제 해결 과정을 기록하고자 만든 기록물입니다.**

<br>

## 📌 CASE 1 : GameManager Blueprint nullptr 접근
&nbsp;**⚠️ 문제 상황**  
&nbsp;&nbsp;&nbsp;&nbsp; → GameManager Blueprint를 World에 배치하였으나 GetActorOfClass()로 가져오려는 시점에서 nullptr 크래시 발생  

&nbsp;**🔍 원인 분석**  
&nbsp;&nbsp;&nbsp;&nbsp; → GameManager가 Cast되는 시점에서 UpdateTextDisplays() 함수를 호출  
&nbsp;&nbsp;&nbsp;&nbsp; → difficultyDisplayActor가 nullptr인 상태에서 TextActor에 FString을 적용하는 과정에서 크래시 발생  

&nbsp;**🛠️ 해결 방안**  
&nbsp;&nbsp;&nbsp;&nbsp; → difficultyDisplayActor->UpdateDisplayValue((float)curDifficulty); 함수 호출 시점을  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;if(difficultyDisplayActor) nullptr 체크 후 함수 호출 될 수 있도록 변경  

&nbsp;**📈 개선 방안**  
&nbsp;&nbsp;&nbsp;&nbsp; → GameModeBase에서 InitGame or BeginPlay 시 월드에 필요한 액터들이 완전히 스폰되었는지 체크 후 초기화 실행  
&nbsp;&nbsp;&nbsp;&nbsp; → nullptr 가능성이 있는 객체 접근 시 방어 코드 작성
