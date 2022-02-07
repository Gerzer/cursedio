//
//  cursedio.h
//  cursedio
//
//  Created by Gabriel Jacoby-Cooper on 2/7/22.
//

#ifndef libcursedio_h
#define libcursedio_h

int copen(const char*, const char*);

int cclose(void);

int cgetc(void);

int cputc(int);

int cseek(long, int);

int cgetpos(fpos_t*);

int csetpos(const fpos_t*);

int cfastforward(void);

void crewind(void);

int cscanf(const char*, ...);

#endif /* libcursedio_h */
