#include <io/path.h>
#include <oak/oak.h>
#include <network/proxy.h>

static double const AppVersion  = 1.0;
static size_t const AppRevision = APP_REVISION;

static void version ()
{
	fprintf(stdout, "%1$s %2$.1f (" COMPILE_DATE " revision %3$zu)\n", getprogname(), AppVersion, AppRevision);
}

static void usage (FILE* io = stdout)
{
	fprintf(io,
		"%1$s %2$.1f (" COMPILE_DATE " revision %3$zu)\n"
		"Usage: %1$s [-hv] ...\n"
		"Options:\n"
		" -h, --help                Show this information.\n"
		" -v, --version             Print version information.\n"
		"\n", getprogname(), AppVersion, AppRevision
	);
}

static void proxy_test (std::string const& url)
{
	proxy_settings_t settings = get_proxy_settings(url);
	if(settings.enabled)
			fprintf(stderr, "server ‘%s’, port %ld, user ‘%s’, password ‘%s’\n", settings.server.c_str(), settings.port, settings.user.c_str(), settings.password.c_str());
	else	fprintf(stderr, "no proxy enabled for reaching ‘%s’\n", url.c_str());
}

int main (int argc, char* const* argv)
{
	// extern char* optarg;
	extern int optind;

	static struct option const longopts[] = {
		{ "help",             no_argument,         0,      'h'   },
		{ "version",          no_argument,         0,      'v'   },
		{ 0,                  0,                   0,      0     }
	};

	int ch;
	while((ch = getopt_long(argc, argv, "hv", longopts, NULL)) != -1)
	{
		switch(ch)
		{
			case 'h': usage();             return 0;
			case 'v': version();           return 0;
			default:  usage(stderr);       return 1;
		}
	}

	argc -= optind;
	argv += optind;

	if(argc == 0)
	{
		proxy_test("https://api.textmate.org/");
	}
	else
	{
		for(int i = 0; i < argc; ++i)
			proxy_test(argv[i]);
	}

	return 0;
}