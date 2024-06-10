using Microsoft.EntityFrameworkCore;
using System.Collections.Generic;

namespace Geld_Guardian.Pages.Data.Models
{
    [PrimaryKey("StatusId")]
    public class PaymentStatus
    {
        public int StatusId { get; set; }
        public string Name { get; set; }


        // one to many relationship with Bill
        public ICollection<Bill> Bills { get; set; }

        public override string ToString()
        {
            return Name;
        }
    }
}
