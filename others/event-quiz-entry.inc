/*  ----------------------------------------------------------------------------------------------------------------------------------------

        Sistema de eventos
                            v0.63
                            Theus_Crazzy (wearLyS)

 ----------------------------------------------------------------------------------------------------------------------------------------- */

#include <YSI_Coding\y_hooks>

// ---------------------------------------------------------------------------------
// Include <samp-random-events>

#if defined _INC_samp_random_event
	#if INC_samp_random_event_version < (5)
		#error Install version 5 or greater of the <samp-random-events> library
	#else
		#if !defined QUIZ_EVENT
			#define QUIZ_EVENT true
			#define QUIZ_EVENT_ID 3
			#define COLOR_QUIZ_EVENT 0xFFF000AA
		#endif
	#endif
#endif

// ---------------------------------------------------------------------------------

enum quizEnum
{
    question[128],
    answers[128]
};

new QUIZ_QUESTION;

new QUIZ_Event[][quizEnum] = 
{
	{ "Qual clube de futebol foi o campe�o mundial de 2004?", "Porto" },
	{ "O que significa a sigla BNS?", "Brasil New Start" },
	{ "Qual pa�s que descobriu o Brasil?", "Portugal" },
	{ "Qual � o jogo mais popular do mundo em 2023?", "Minecraft" },
	{ "Qual � o maior estado do Brasil?", "Amazonas" },
    { "Qual � o estado mais rico dos Estados Unidos da Am�rica?", "California" },
    { "Qual � a cidade mais populosa da Am�rica do Sul?", "S�o Paulo" },
    { "Em que ano come�ou a guerra da Cisplatina?", "1825" },
    { "Qual era o nome da uni�o de Portugal e Brasil antes da Independ�ncia do Brasil?", "Reino Unido de Portugal, Brasil e Algarves" },
    { "Qual � a alian�a militar mais antiga do mundo?", "Alian�a Anglo-Portuguesa" },
    { "Qual � o jogo famoso que tem criatividade de constru��o?", "Roblox" },
    { "Qual � o quarto distrito mais populoso de Portugal?", "Braga" },
    { "Quem � o criador do servidor?", "Theus_Crazzy" },
    { "Quem � o programador aprendiz do servidor?", "Joao_Revolts" },
    { "Que grupo resolve as coisas mais importantes do servidor?", "Conselho" },
    { "Qual � a capital do estado do Paran�?", "Curitiba" },
    { "Qual foi o primeiro Imp�rio colonial do mundo?", "Imp�rio Portugu�s" },
    { "Aonde foi sediado a Copa do Mundo de 2018?", "R�ssia" },
    { "Com quantas horas jogadas voc� precisa para usar o /noob?", "1" },
    { "Qual era o nome antigo da organiza��o Crips?", "Seville Boulevard" },
    { "Qual � a capital do estado do Amazonas?", "Manaus" },
    { "Quem era a antiga respons�vel pela equipe de desenvolvimento?", "KatarinaJensen" },
    { "Em que ano foi proclamado a Rep�blica no Brasil?", "1889" },
    { "Qual � o nome da mesma fam�lia real do Brasil e Portugal?", "Bragan�a" },
    { "Aonde foi inventado a Pizza?", "It�lia" },
    { "Qual � o pa�s da �frica que � tem o menor IDH?", "Sud�o do Sul" },
    { "Em que ano foi fundado a comunidade da Austr�lia?", "1901" },
    { "Qual � a pen�nsula que Portugal e Espanha est�o localizados?", "Pen�nsula Ib�rica" },
    { "Em que ano a hist�ria do Brasil New Start come�ou?", "2012" },
    { "Qual foi o Presidente que ganhou o Pr�mio Nobel da Paz de 1993?", "Nelson Mandela" },
    { "O que significa BTC?", "Bitcoin" },
    { "Qual foi o primeiro-ministro que governou o Reino Unido durante a Segunda Guerra Mundial?", "Winston Churchill" },
    { "Quantos dias tem um ano civil?", "365 dias" },
    { "Qual � a linguagem de programa��o mais usada e solicitada?", "Java" },
    { "Qual � o nome da Intelig�ncia Artificial usada para pedir muita ajuda?", "ChatGPT" },
    { "Em que ano foi fundado o WhatsApp?", "2009" }
};

hook OnPlayerText(playerid, text[])
{
	new string[128];

	if (EVENT[ev_started] && EVENT[ev_type] == QUIZ_EVENT_ID)
	{
        if (strlen(text) > 50) return 1;

        if (strdistance(QUIZ_Event[QUIZ_QUESTION][answers], text) < 5)
        {
            if (gettime() < GetPVarInt(playerid, #varFloodRespostas))
                return SendClientMessage(playerid, -1, "V� com calma! Voc� n�o � o Einstem... Responda sem robos...");

            SetPVarInt(playerid, #varFloodRespostas, gettime() + 2);

            EVENT[ev_score][playerid]++;
            EVENT[ev_bonus][playerid] += 500;

            SendMsgAllF(EVENT[ev_color], "[EVENTO QUIZ]: {FFFFFF}%s acertou a resposta, {FFFFFF}adicionado {00AA00}+$500", PlayerName[playerid]);

            PlayerTextDrawChangeString(string, playerid, "%s", event_ptextdraw[0][playerid], PlayerName[playerid]);
            PlayerTextDrawChangeString(string, playerid, "%d acertos", event_ptextdraw[1][playerid], EVENT[ev_score][playerid]);

            EVENT_UpdateRanks();

            QUIZ_QUESTION = random(sizeof(QUIZ_Event));
		    SendMsgAllF(EVENT[ev_color], "[EVENTO QUIZ]: {00FF00}%s", QUIZ_Event[QUIZ_QUESTION][question]);
        }
	}
	return 1;
}