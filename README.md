Drush Verify Make module
========================

Drush module which verifies the drush makefile with an existing installation path
by generating a checksum file. It skips the make when the checksums match.

It generates a checksum file in the build path the first time your run `drush make`.
The second time run `drush make` you have to add `--verify-make-path=<path>` argument so it can
verify agains the checksum file.


Usage
-----

* Copy `verify_make.drush.inc` to `~/.drush`

* Run your drush make command, for example:

	drush make project.make build/
        mv build public

* Rerun your drush make command with the verify argument

	drush make project.make --verify-make-path=public build/


License
-------

MIT
