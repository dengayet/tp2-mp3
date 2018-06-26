#include <stdlib.h>
#include <string.h>
#include "mp3.h"

char * genres[MAX_GENRES]=
{
        "Blues",
        "Classic Rock",
        "Country",
        "Dance",
        "Disco",
        "Funk",
        "Grunge",
        "Hip-Hop",
        "Jazz",
        "Metal",
        "New Age",
        "Oldies",
        "Other",
        "Pop",
        "R&B",
        "Rap",
        "Reggae",
        "Rock",
        "Techno",
        "Industrial",
        "Alternative",
        "Ska",
        "Death Metal",
        "Pranks",
        "Soundtrack",
        "Euro-Techno",
        "Ambient",
        "Trip-Hop",
        "Vocal",
        "Jazz+Funk",
        "Fusion",
        "Trance",
        "Classical",
        "Instrumental",
        "Acid",
        "House",
        "Game",
        "Sound Clip",
        "Gospel",
        "Noise",
        "AlternRock",
        "Bass",
        "Soul",
        "Punk",
        "Space",
        "Meditative",
        "Instrumental Pop",
        "Instrumental Rock",
        "Ethnic",
        "Gothic",
        "Darkwave",
        "Techno-Industrial",
        "Electronic",
        "Pop-Folk",
        "Eurodance",
        "Dream",
        "Southern Rock",
        "Comedy",
        "Cult",
        "Gangsta",
        "Top 40",
        "hristian Rap",
        "Pop/Funk",
        "Jungle",
        "Native American",
        "Cabaret",
        "New Wave",
        "Psychadelic",
        "Rave",
        "Showtunes",
        "Trailer",
        "Lo-Fi",
        "Tribal",
        "Acid Punk",
        "Acid Jazz",
        "Polka",
        "Retro",
        "Musical",
        "Rock & Roll",
        "Hard Rock",
        "Folk",
        "Folk-Rock",
        "National Folk",
        "Swing",
        "Fast Fusion",
        "Bebob",
        "Latin",
        "Revival",
        "Celtic",
        "Bluegrass",
        "Avantgarde",
        "Gothic Rock",
        "Progressive Rock",
        "Psychedelic Rock",
        "Symphonic Rock",
        "Slow Rock",
        "Big Band",
        "Chorus",
        "Easy Listening",
        "Acoustic",
        "Humour",
        "Speech",
        "Chanson",
        "Opera",
        "Chamber Music",
        "Sonata",
        "Symphony",
        "Booty Brass",
        "Primus",
        "Porn Groove",
        "Satire",
        "Slow Jam",
        "Club",
        "Tango",
        "Samba",
        "Folklore",
        "Ballad",
        "Poweer Ballad",
        "Rhytmic Soul",
        "Freestyle",
        "Duet",
        "Punk Rock",
        "Drum Solo",
        "A Capela",
        "Euro-House",
        "Dance Hall",
};

status_t ADT_Track_new_from_binary_file (FILE * f, ADT_Track_t ** track) /*debería dividir en ADT..New y ADT..load?*/
{
    status_t st;
    char buf[MP3_HEADER_SIZE];
    char *temp;
    char header[MP3_HEADER_SIZE + 1];

    if (track == NULL || f == NULL)
        return ERROR_NULL_POINTER;
    if ((*track = (ADT_Track_t *) malloc(sizeof(ADT_Track_t))) == NULL)
        return ERROR_OUT_OF_MEMORY;
    if ((st = read_header(f, header)) != OK)
        {/*no recuerdo como se hace esto jeje*/ /*Que??*/
            free(*track);
            return st;
        }
    memcpy((*track)->tag, header + LEXEM_START_TAG, LEXEM_SPAN_TAG);
    ((*track)->tag)[LEXEM_SPAN_TAG] = '\0';
    memcpy((*track)->title,header + LEXEM_START_TITLE, LEXEM_SPAN_TITLE);
    ((*track)->title)[LEXEM_SPAN_TITLE] = '\0';
    memcpy((*track)->artist, header + LEXEM_START_ARTIST, LEXEM_SPAN_ARTIST);
    ((*track)->artist)[LEXEM_SPAN_ARTIST] = '\0';
    memcpy((*track)->album, header + LEXEM_START_ALBUM, LEXEM_SPAN_ALBUM);
    ((*track)->album)[LEXEM_SPAN_ALBUM] = '\0';
    memcpy(buf, header + LEXEM_START_YEAR, LEXEM_SPAN_YEAR);
    buf[LEXEM_SPAN_YEAR] = '\0';
    (*track)->year = (short)strtol(buf, &temp, 10); /*fulero*/
    if(*temp)
    {
        free(*track);
        return ERROR_INVALID_ARGUMENTS;
    } /*cambiar */
    memcpy((*track)->genre, header + LEXEM_START_GENRE, LEXEM_SPAN_GENRE); /*revisar*/
    buf[LEXEM_SPAN_GENRE] = '\0';  /*cual es el sentido de esto <--- ¿?*/
    return OK;
}

status_t read_header(FILE * f, char * header) /*ya necesito memoria reservada para no usar mem din*/
{
    long int length;

    if (header == NULL || f == NULL)
        return ERROR_NULL_POINTER;
    if((fseek(f, 0, SEEK_END))!=0)
        return ERROR_CANNOT_OPEN_FILE;
    length = ftell(f);
    fseek(f,length-MP3_HEADER_SIZE,SEEK_SET);
    fread(header, sizeof(char), MP3_HEADER_SIZE, f);

    return OK;
}

status_t ADT_Track_delete (ADT_Track_t ** track)
{
    if(track == NULL)
        return ERROR_NULL_POINTER;
    free (*track);
    (*track) = NULL;
    return OK;
}

status_t ADT_Track_print_to_csv (FILE * fo, ADT_Track_t * track)
{
    if(fo == NULL || track == NULL)
        return ERROR_NULL_POINTER;
    fprintf(fo, "%s|%s|%s|%s|%d|%s", track->tag, track->title, track->artist, track->album, track->year, track->genre);
    return OK;
}

status_t ADT_Track_print_to_xml (FILE * fo, ADT_Track_t * track)
{
    if(fo == NULL || track == NULL)
        return ERROR_NULL_POINTER;
    fprintf(fo,"\t<track>");
    fprintf(fo,"\t<tag>%s</tag>\n", track->tag);
    fprintf(fo,"\t\t<title>%s</title>\n", track->title);
    fprintf(fo,"\t\t\t<artist>%s</artist>\n", track->artist);
    fprintf(fo,"\t\t\t\t<album>%s</album>\n", track->album);
    fprintf(fo,"\t\t\t\t\t<year>%d</year>\n", track->year);
    fprintf(fo,"\t\t\t\t\t\t<genre>%s</genre>\n", track->genre);
    return OK;
}
int compare_strings(const char *s1,const char *s2)
{
    return strcmp(s1,s2);
}
int compare_by_genre(const void *pv1, const void *pv2)
{
    ADT_Track_t *p1,*p2;

    p1=(ADT_Track_t *)pv1;
    p2=(ADT_Track_t *)pv2;
    if(p1==NULL || p2==NULL)
        return ERROR_NULL_POINTER;

    return compare_strings(p1->genre,p2->genre);
}

int compare_by_artist(const void *pv1, const void *pv2)
{
    ADT_Track_t *p1,*p2;

    p1=(ADT_Track_t *)pv1;
    p2=(ADT_Track_t *)pv2;
    if(p1==NULL || p2==NULL)
        return ERROR_NULL_POINTER;

    return strcmp(p1->artist,p2->artist);
}

int compare_by_tag(const void *pv1, const void *pv2)
{
    ADT_Track_t *p1,*p2;

    p1=(ADT_Track_t *)pv1;
    p2=(ADT_Track_t *)pv2;
    if(p1==NULL || p2==NULL)
        return ERROR_NULL_POINTER;

    return strcmp(p1->tag,p2->tag);
}


