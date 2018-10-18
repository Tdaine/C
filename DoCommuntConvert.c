#include"DoCommuntConvert.h"

void DoNULState(FILE*pfIn, FILE*pfOut, enum State* ps)
{
	int first = fgetc(pfIn);
	switch (first)
	{
	case '/': 
	{
		int second = fgetc(pfIn);
		switch (second)
		{
		case '/': {
			fputc(first, pfOut);
			fputc(second, pfOut);
			*ps = CPP_STATE;
			break;
			}
		case '*': {
			fputc('/', pfOut);
			fputc('/', pfOut);
			*ps = C_STATE;
			break;
		}
		default: {
			fputc(first, pfOut);
			fputc(second, pfOut);
			break;
		}
		}
		break;
	}
	case EOF:
	{
		*ps = END_STATE;
		break;
	}
	default:
	{
		fputc(first, pfOut);
		break;
	}
	}
}

void DoCLState(FILE*pfIn, FILE*pfOut, enum State* ps)
{
	int first = fgetc(pfIn);
	switch (first)
	{
	case '*': {
		int second = fgetc(pfIn);
		switch (second)
		{
		case '/': {
			int ch;
			if ((ch = fgetc(pfIn)) != '\n')
			{
				ungetc(ch, pfIn);
				fputc('\n', pfOut);
			}
			else
				ungetc(ch, pfIn);
			*ps = NUL_STATE;
			break;
		}
		case '\n': {
			fputc(first, pfOut);
			fputc('\n', pfOut);
			fputc('/', pfOut);
			fputc('/', pfOut);
			break;
		}
		case '*': {
			fputc(first, pfOut);
			ungetc(second, pfIn);
			break;
		}
		default: {
			fputc(first, pfOut);
			break;
		}

		}
		break;
	}
	case '\n': {
		int c;
		if ((c = fgetc(pfIn)) != '*')
		{
			fputc(first, pfOut);
			ungetc(c, pfIn);
			fputc('/', pfOut);
			fputc('/', pfOut);
		}
		else
			ungetc(c, pfIn);
		break;
		
	}
	default: {
		fputc(first, pfOut);
		break;
	}

	}

}

void DoCppState(FILE*pfIn, FILE*pfOut, enum State* ps)
{
	int ch = fgetc(pfIn);
	switch (ch)
	{
	case '\n': {
		fputc(ch, pfOut);
		*ps = NUL_STATE;
		break;
	}
	case EOF: {
		*ps = END_STATE;
		break;
	}
	default: {
		fputc(ch, pfOut);
		break;
	}

	}
}

void DoCommentConvert(FILE*pfIn, FILE*pfOut)
{
	enum State state = NUL_STATE;
	while (state != END_STATE)
	{
		switch (state)
		{
		case NUL_STATE:
			DoNULState(pfIn,pfOut,&state);
			break;
		case C_STATE:
			DoCLState(pfIn, pfOut, &state);
			break;
		case CPP_STATE:
			DoCppState(pfIn, pfOut, &state);
			break;
		}
	}
}


