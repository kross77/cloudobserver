#ifndef HTTP_RESPONSE_PARSER_STATE_H
#define HTTP_RESPONSE_PARSER_STATE_H

enum http_response_parser_state
{
	VERSION,
	STATUS,
	DESCRIPTION,
    HEADER_KEY,
    HEADER_VALUE,
    BODY,
    OK
};

#endif // HTTP_RESPONSE_PARSER_STATE_H
