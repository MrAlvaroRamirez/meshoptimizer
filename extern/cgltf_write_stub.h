
// struct from cgltf_write.h
typedef struct {
	char* buffer;
	cgltf_size buffer_size;
	cgltf_size remaining;
	char* cursor;
	cgltf_size tmp;
	cgltf_size chars_written;
	const cgltf_data* data;
	int depth;
	const char* indent;
	int needs_comma;
	uint32_t extension_flags;
	uint32_t required_extension_flags;
} cgltf_write_context;

#define CGLTF_SPRINTF(...) { \
		context->tmp = snprintf ( context->cursor, context->remaining, __VA_ARGS__ ); \
		context->chars_written += context->tmp; \
		if (context->cursor) { \
			context->cursor += context->tmp; \
			context->remaining -= context->tmp; \
		} }

#ifdef FLT_DECIMAL_DIG
	// FLT_DECIMAL_DIG is C11
	#define CGLTF_DECIMAL_DIG (FLT_DECIMAL_DIG)
#else
	#define CGLTF_DECIMAL_DIG 9
#endif

static void cgltf_write_indent(cgltf_write_context* context)
{
	if (context->needs_comma)
	{
		CGLTF_SPRINTF(",\n");
		context->needs_comma = 0;
	}
	else
	{
		CGLTF_SPRINTF("\n");
	}
	for (int i = 0; i < context->depth; ++i)
	{
		CGLTF_SPRINTF("%s", context->indent);
	}
}

static void cgltf_write_line(cgltf_write_context* context, const char* line)
{
	if (line[0] == ']' || line[0] == '}')
	{
		--context->depth;
		context->needs_comma = 0;
	}
	cgltf_write_indent(context);
	CGLTF_SPRINTF("%s", line);
	cgltf_size last = (cgltf_size)(strlen(line) - 1);
	if (line[0] == ']' || line[0] == '}')
	{
		context->needs_comma = 1;
	}
	if (line[last] == '[' || line[last] == '{')
	{
		++context->depth;
		context->needs_comma = 0;
	}
}

static void cgltf_write_strprop(cgltf_write_context* context, const char* label, const char* val)
{
	if (val)
	{
		cgltf_write_indent(context);
		CGLTF_SPRINTF("\"%s\": \"%s\"", label, val);
		context->needs_comma = 1;
	}
}

static void cgltf_write_intprop_strict(cgltf_write_context* context, const char* label, int val)
{
	cgltf_write_indent(context);
	CGLTF_SPRINTF("\"%s\": %d", label, val);
	context->needs_comma = 1;
}

static void cgltf_write_floatprop_strict(cgltf_write_context* context, const char* label, float val)
{
	cgltf_write_indent(context);
	CGLTF_SPRINTF("\"%s\": ", label);
	CGLTF_SPRINTF("%g", val);
	context->needs_comma = 1;

	if (context->cursor)
	{
		char *decimal_comma = strchr(context->cursor - context->tmp, ',');
		if (decimal_comma)
		{
			*decimal_comma = '.';
		}
	}
}

static void cgltf_write_boolprop_strict(cgltf_write_context* context, const char* label, bool val)
{
	cgltf_write_indent(context);
	CGLTF_SPRINTF("\"%s\": %s", label, val ? "true" : "false");
	context->needs_comma = 1;
}

static void cgltf_write_intarrayprop(cgltf_write_context* context, const char* label, const cgltf_int* vals, cgltf_size dim)
{
	cgltf_write_indent(context);
	CGLTF_SPRINTF("\"%s\": [", label);
	for (cgltf_size i = 0; i < dim; ++i)
	{
		if (i != 0)
		{
			CGLTF_SPRINTF(", %d", vals[i]);
		}
		else
		{
			CGLTF_SPRINTF("%d", vals[i]);
		}
	}
	CGLTF_SPRINTF("]");
	context->needs_comma = 1;
}

static void cgltf_write_floatarrayprop(cgltf_write_context* context, const char* label, const cgltf_float* vals, cgltf_size dim)
{
	cgltf_write_indent(context);
	CGLTF_SPRINTF("\"%s\": [", label);
	for (cgltf_size i = 0; i < dim; ++i)
	{
		if (i != 0)
		{
			CGLTF_SPRINTF(", %.*g", CGLTF_DECIMAL_DIG, vals[i]);
		}
		else
		{
			CGLTF_SPRINTF("%.*g", CGLTF_DECIMAL_DIG, vals[i]);
		}
	}
	CGLTF_SPRINTF("]");
	context->needs_comma = 1;
}

