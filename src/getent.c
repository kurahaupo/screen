#include <sys/types.h>
#include <grp.h>
#include <malloc.h>
#include <pwd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *  Implementation of getpwnam & getgrnam for static linking.
 *  Only reads /etc/passwd & /etc/group
 */

/******************************************************************************/

/*
 * next_field is like strtok but without internal state.
 * It still overwrites delimiters, but the caller provides &ptr to carry the
 * progression state.
 */

static char * next_field(char **pp, char delim) {
    char *p = *pp;
    if (!p)
        return NULL;
    char *q = strchr(p, delim);
    if (q && delim)
        *q++ = 0;
    else
        q = NULL;
    *pp = q;
    return p;
}

static char * keep( char * p ) {
    if (!p) return NULL;
    if (!*p) return NULL;
    return strdup(p);
}

/******************************************************************************/

static struct group *groups = NULL;

static void load_groups(void) {
    if (groups)
        return;
    FILE *f = fopen("/etc/group", "r");
    size_t res = 2,
           next = 0;
    groups = malloc(res * sizeof *groups);
    while (1) {
        char buf[1024];
        char *p = fgets(buf, sizeof buf, f);
        if (!p)
            break;
        p = strchr(buf, 0);
        if (p == buf || p[-1] != '\n')
            break;

        if (next+2 > res) {
            res <<= 1, res |= next+2 | res-1;
            groups = realloc(groups, res * sizeof *groups);
        }
        struct group *g = groups + next++;
        *g = (struct group){ .gr_name = NULL };

        *--p = ':';   /* prune trailing newline */
        p = buf;

        g->gr_name = keep(next_field(&p, ':'));
        next_field(&p, ':'); /* skip obsolete password field */
        g->gr_gid = atoi(next_field(&p, ':'));
        /* ignore gr_mem and all further fields, since we don't use them */
    }
    groups[next++] = (struct group){ .gr_name = NULL };
    groups = realloc(groups, next * sizeof *groups);
    fclose(f);
}

static struct passwd *users = NULL;

static void load_users(void) {
    if (users)
        return;
    FILE *f = fopen("/etc/passwd", "r");
    size_t res = 2,
           next = 0;
    users = malloc(res * sizeof *users);
    while (1) {
        char buf[1024];
        char *p = fgets(buf, sizeof buf, f);
        if (!p)
            break;
        p = strchr(buf, 0);
        if (p == buf || p[-1] != '\n')
            break;

        if (next+2 > res) {
            res <<= 1, res |= next+2 | res-1;
            users = realloc(users, res * sizeof *users);
        }
        struct passwd *u = users + next++;
        *u = (struct passwd){ .pw_name = NULL };

        *--p = ':';   /* prune trailing newline */
        p = buf;

        u->pw_name = keep(next_field(&p, ':'));
        next_field(&p, ':'); /* skip obsolete password field */
        u->pw_uid = atoi(next_field(&p, ':'));
        u->pw_gid = atoi(next_field(&p, ':'));
        next_field(&p, ':'); /* skip pw_gecos, since we don't use it */
        u->pw_dir = keep(next_field(&p, ':'));
        u->pw_shell = keep(next_field(&p, ':'));
    }
    users[next++] = (struct passwd){ .pw_name = NULL };
    users = realloc(users, next * sizeof *users);
    fclose(f);
}

/******************************************************************************/

struct group *getgrnam(const char *name) {
    load_groups();
    for (struct group *g = groups; g->gr_name; ++g)
        if (!strcmp(g->gr_name, name))
            return g;
    return NULL;
}

struct group *getgrgid(gid_t gid) {
    load_groups();
    for (struct group *g = groups; g->gr_name; ++g)
        if (g->gr_gid == gid)
            return g;
    return NULL;
}

struct passwd *getpwnam(const char *name) {
    load_users();
    for(struct passwd *u = users;u->pw_name;++u)
        if (!strcmp(u->pw_name, name))
            return u;
    return NULL;
}

struct passwd *getpwuid(uid_t uid) {
    load_users();
    for (struct passwd *u = users; u->pw_name; ++u)
        if (u->pw_uid == uid)
            return u;
    return NULL;
}
