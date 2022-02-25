#define MAX_STR_LENGTH 4096

stock void CString(char[] str, int len)
{
	static int i, j, n, cb;
	static char temp[MAX_STR_LENGTH];
	
	for (i = 0, j = 0; i < len && str[i] != 0; i++)
	{
		cb = GetCharBytes(str[i]);
		// два байта (208/209 + код)
		if (cb == 2) 
		{
			switch (str[i+1])
			{
				/* a */ case (176): temp[j++] = 97;
				/* o */ case (190): temp[j++] = 111;
				/* е */ case (181): temp[j++] = 101;
				/* y */ case (131): temp[j++] = 121;
				/* p */ case (128): temp[j++] = 112;
				/* c */ case (129): temp[j++] = 99;
				/* x */ case (133): temp[j++] = 120;
				/* А */ case (144): temp[j++] = 65;
				/* О */ case (158): temp[j++] = 79;
				/* Е */ case (149): temp[j++] = 69;
				/* С */ case (161): temp[j++] = 67;
				/* Х */ case (165): temp[j++] = 88;
				/* Р */ case (160): temp[j++] = 80;
				/* Н */ case (157): temp[j++] = 72;
				/* В */ case (146): temp[j++] = 66;
				/* Т */ case (162): temp[j++] = 84;
				/* К */ case (154): temp[j++] = 75;
				/* М */ case (156): temp[j++] = 77;
				/* З */ case (151): temp[j++] = 51;
				
				default:
				{
					temp[j++] = str[i];
					temp[j++] = str[i+1];
				}
			}
		}
		else
		{
			for(n = i; n < i+cb; n++)
			{
				temp[j++] = str[n];
				if(j >= MAX_STR_LENGTH - 1)
				{
					i = len;
					break;
				}
			}
		}
		i += cb - 1;
	}
	
	// Копирование в изначальную строку
	strcopy(str, len, temp);
	
	// Конец строки (0)
	if(len <= j && len != 0 )
	{
		if(len >= 2 && (str[len-2] == 208 || str[len-2] == 209)) str[len-2] = 0;
		str[len-1] = 0;
	}
	else
	{
		if(j != 0 && (str[j-1] == 208 || str[j-1] == 209)) str[j-1] = 0;
		str[j] = 0;
	}
}

stock void CTitle(Menu menu, const char[] str, any ...)
{
	int len = strlen(str) + 1024;
	char[] res = new char[len];
	VFormat(res, len, str, 3);
	CString(res, len);
	SetMenuTitle(menu, res);
}

stock bool CItem(Menu menu, const char[] info, const char[] str, int style = ITEMDRAW_DEFAULT, any ...)
{
	int len = strlen(str) + 1024;
	char[] res = new char[len];
	VFormat(res, len, str, 5);
	CString(res, len);
	return AddMenuItem(menu, info, res, style);
}