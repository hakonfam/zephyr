#pragma once

// TODO: Use portable header guard

// TODO: Use normal declaration?
// TODO: Use extern ?
// extern void __stdout_hook_install(int (*hook)(int)); // ?
static int (*_stdout_hook)(int);

// TODO: Add __stdout_hook_install to this header and make users use
// it.
