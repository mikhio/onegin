#ifndef IOG_STRING_H
#define IOG_STRING_H


size_t istrlen ( const char *str );

const char *istrchr ( const char *str, char character );

int istrcat(char *dest, const char *source);
int istrcpy ( char *dest, const char *source );
int istrcmp ( const char *str1, const char *str2 ); // TODO: Add right to left mode
                                                    


#endif // IOG_STRING_H
