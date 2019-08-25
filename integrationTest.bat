cd C:\Users\RJ\source\repos\Sailer

mkdir build
cd build

cmake ..
msbuild Sailer.sln

cd ../test
mkdir build
cd build

cmake ..
msbuild SailerTest.sln

cd Debug
SailerTest.exe > result.txt

if errorlevel 0 (
    python ../../../DiscordSendWebhook.py https://discordapp.com/api/webhooks/615294872886444047/vYoaZJzKKJL4wkTqg87PLMIcXOAtz0DFMXE1dD1R9CQs-c-GbwOEXhfZIKwyXX0PE9pi "%date%:%time% Integration Build Passed" IntegrationBot
    PAUSE
    exit /b %errorlevel%
)
else (
    python ../../../DiscordSendWebhook.py https://discordapp.com/api/webhooks/615294872886444047/vYoaZJzKKJL4wkTqg87PLMIcXOAtz0DFMXE1dD1R9CQs-c-GbwOEXhfZIKwyXX0PE9pi "%date%:%time% Integration Build Failed" IntegrationBot
    PAUSE
    exit /b %errorlevel%
)

