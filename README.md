# pam-validity
PAM validity module to work with python-validity

Currently supports the following sensors:

138a:0090 Validity Sensors, Inc. VFS7500 Touch Fingerprint Sensor
138a:0097 Validity Sensors, Inc.
06cb:009a Synaptics, Inc. Which are present in various ThinkPad and HP laptops.

Hi this is a module created to get avail from pam-validity so you can authenticate. 
This is a very simple module

You need to install python-validity 1st and have at least a user and a finger enrolled
see https://github.com/uunicorn/python-validity (KUDOS)

What you have to do:

1. Install python-validity in /usr/local/bin/python-validity and enroll at least one finger with any user ID (SID), as shown there on the example on their site

2. Install pam development package of your distro, in Fedora it is pam-devel

3. Download pam_validity.c in any directory and compile with 

 "# gcc -fPIC -fno-stack-protector -c pam_validity.c"

4. Install produced pam_valadity.o to pam modules directory

"# ld -x --shared -o /usr/lib64/security/pam_validity.so pam_validity.o"

/usr/lib64/security is the directory in which fedora saves pam modules (you will see many pam_* modules there), find where it is in your distro

5. Download and copy pam_validity.sh to/usr/local/bin/python-validity

6. Add the following to any pam config file in /etc/pam.d/ you want to have fingerprint auth. I added mine to gdm-password, su and sudo.

 auth		sufficient	pam_validity.so
 
 account sufficient  pam_validity.so

Good luck!

P.S. I just did this for fun and I am no programmer. You can open a ticket but I am not sure I can solve. I want to add features  but we will see....

P.S.2 On 1st gdm login you might get a prompt to unlock the keyring. Unfortunately this is a known issue and only unlocks with a password. 
