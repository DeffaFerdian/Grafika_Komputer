const no_telepon = document.getElementById("no_telepon")
const form = document.getElementById("form")
const errorElement = document.getElementById("error")

form.addEventListener('submit', (e) => {
  let messages = []
  if (no_telepon.value.length >= 2){
  messages.push('nomor telepon harus 12 angka')}
  
  if(messages.length > 0){
    e.preventDefault()
    errorElement.innerText = messages.join('')
  }

})