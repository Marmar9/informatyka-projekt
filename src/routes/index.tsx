import { component$, useVisibleTask$, useSignal } from "@builder.io/qwik";
import type { DocumentHead } from "@builder.io/qwik-city";

declare global {
  interface Window {
    wasm: WebAssembly.WebAssemblyInstantiatedSource;
  }
}

function readStringFromMemory(memory: Uint8Array, pointer: number): string {
  const utf8decoder = new TextDecoder("utf-8");
  let string = "";
  let i = 0;
  let char = "";

  while (char !== "\0") {
    string += char;
    char = utf8decoder.decode(new Uint8Array([memory[pointer + i]]));
    i++;
  }

  return string;
}

export default component$(() => {
  const isLoading = useSignal<boolean>(true);
  const text = useSignal<string | undefined>(undefined);
  const option = useSignal<string>("encrypt");
  const result = useSignal<string>("");
  const key = useSignal<string>("2");
  // eslint-disable-next-line qwik/no-use-visible-task
  useVisibleTask$(async () => {
    const importsObject: WebAssembly.Imports = {
      wasi_snapshot_preview1: {
        proc_exit: (...args: any) => {
          console.log("proc_exit", args);
        },
      },
    };

    WebAssembly.instantiateStreaming(fetch("/main.wasm"), importsObject).then(
      (wasm) => {
        console.log("wasm", wasm);
        window.wasm = wasm;

        isLoading.value = false;
      },
    );
  });

  return (
    <>
      <h1 class="text-4xl">Encrypt/decrypt ⌨️</h1>

      {isLoading.value ? (
        <h2>loading...</h2>
      ) : (
        <form class="mt-5 flex w-96 flex-col gap-5">
          <div class="flex flex-col">
            <label for="text">Text</label>
            <input
              type="text"
              name=""
              id="text"
              placeholder="Text"
              class="rounded border-b-2 border-gray-200"
              bind:value={text}
            />
          </div>
          <div class="flex flex-col">
            <label for="key">Key</label>
            <input
              type="key"
              name=""
              id="key"
              placeholder="Text"
              class="rounded border-b-2 border-gray-200"
              bind:value={key}
            />
          </div>
          <select
            aria-label="Default select example"
            onChange$={(event) =>
              (option.value = (event.target as HTMLSelectElement).value)
            }
          >
            <option value="encrypt">Encrypt</option>
            <option value="decrypt">Decrypt</option>
          </select>
          <button
            onClick$={() => {
              if (text.value) {
                console.log(option.value);

                const encoder = new TextEncoder();
                const memoryBuffer = new Uint8Array(
                  window.wasm.instance.exports.memory.buffer,
                );

                const str = text.value;
                const encodedStr = encoder.encode(str);

                memoryBuffer.set(encodedStr, 0);
                let pointer = undefined;

                const key_ = Number(key.value);
                if (Number.isNaN(key_)) {
                  alert("Key must be a number");
                  return;
                }

                if (option.value === "encrypt") {
                  pointer = window.wasm.instance.exports.encryptRailFence(
                    0,
                    encodedStr.length,
                    key_,
                  );
                } else {
                  pointer = window.wasm.instance.exports.decryptRailFence(
                    0,
                    encodedStr.length,
                    key_,
                  );
                }

                const resultStr = readStringFromMemory(memoryBuffer, pointer);

                window.wasm.instance.exports.freeMemory(pointer);
                result.value = resultStr;
                text.value = "";
              }
            }}
            type="button"
            class="mt-4 h-10 w-32 transform rounded-lg border-2 border-gray-300 transition-transform duration-150 ease-in-out hover:border-gray-400 active:scale-95"
          >
            Compute
          </button>
        </form>
      )}

      {result.value && <span>Result: {result.value}</span>}
    </>
  );
});

export const head: DocumentHead = {
  title: "Welcome",
  meta: [
    {
      name: "description",
      content: "Qwik site description",
    },
  ],
};
