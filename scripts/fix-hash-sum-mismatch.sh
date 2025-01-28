#! /bin/bash

# # # # # # #
# Temporary #
# # # # # # #
# sudo mv /var/lib/apt/lists /var/lib/apt/lists_bkup
# sudo apt-get update -o Acquire::CompressionTypes::Order::=gz
# sudo apt-get clean && sudo apt-get update && sudo rm -rf /var/lib/apt/lists/*

# # # # # # #
# Permanent #
# # # # # # #
sudo apt-get clean
export FILENAME="/etc/apt/apt.conf.d/99force-gzip"
export REQUIRED_STRING="Acquire::CompressionTypes::Order { \"gz\"; };"

echo "[ Fixing hash sum mismatch ... ]"
if [[ ! -f "$FILENAME" ]] ; then
  echo "> Create $FILENAME with gz priority ..."
  sudo bash -c 'echo "Acquire::CompressionTypes::Order { \"gz\"; };" >> /etc/apt/apt.conf.d/99force-gzip'
else
  if [[ $(grep -c "$REQUIRED_STRING" "$FILENAME") -ge 1 ]]; then
    echo "> Already gz format is priortized."
  else
    echo "> Already file ($FILENAME) exists, but gz format is not priortized."
  fi
fi

echo ""

echo "[ Updating apt list ... ]" &&
sudo apt-get update -qq &&
echo "> DONE"


# Check
# apt-config dump | grep Acquire::CompressionTypes::Order